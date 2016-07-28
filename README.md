# YYModel---Demo
丰富的例子展示了怎么使用YYModel
**开篇说明：**
虽然网上有很多讲解YYModel使用方法的文章，包括YYModel作者也在github上对其做了使用说明。
但在我实际使用过程中，依然发现文档的不完善，比如对于复杂的模型（如多层嵌套）讲解的仍不透彻，同时本文也会介绍一神器配合YYModel使用，让你感受分分钟搞定模型创建的酸爽。
当然为了减少读者的学习成本，本会对YYModel作者的文档进行丰富和扩展。
可在github上下载[Demo](https://github.com/walkertop/YYModel---Demo)，以便更直观了解各种使用场景详细代码。
文章只要包含：
> - 1. 详解YYModel的多种使用场景
> - 2. 拓展插件，让你一分钟搞定所有的模型的创建和调用。
--------
## 一、YYModel的使用场景
### 1.简单的 Model 与 JSON 相互转换

```
// JSON:
{
    "uid":123456,
    "name":"Harry",
    "created":"1965-07-31T00:00:00+0000"
}

// Model:
@interface User : NSObject
@property UInt64 uid;
@property NSString *name;
@property NSDate *created;
@end

@implementation User

@end
```
--------
```
// 将 JSON (NSData,NSString,NSDictionary) 转换为 Model:
User *user = [User yy_modelWithJSON:json];

// 将 Model 转换为 JSON 对象:
NSDictionary *json = [user yy_modelToJSONObject];
```

 JSON/Dictionary 中的对象类型与 Model 属性不一致时，YYModel 将会进行如下自动转换。自动转换不支持的值将会被忽略，以避免各种潜在的崩溃问题。
![格式自动转换.png](http://upload-images.jianshu.io/upload_images/1467716-33ae643a0ca314fa.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
--------

#### 2.Model 属性名和 JSON 中的 Key 不相同

```
// JSON:
{
    "n":"Harry Pottery",
    "p": 256,
    "ext" : {
        "desc" : "A book written by J.K.Rowing."
    },
    "ID" : 100010
}

// Model:
@interface Book : NSObject
@property NSString *name;
@property NSInteger page;
@property NSString *desc;
@property NSString *bookID;
@end
@implementation Book
//返回一个 Dict，将 Model 属性名对映射到 JSON 的 Key。
+ (NSDictionary *)modelCustomPropertyMapper {
    return @{@"name" : @"n",
             @"page" : @"p",
             @"desc" : @"ext.desc",
             @"bookID" : @[@"id",@"ID",@"book_id"]};
}
@end
```
你可以把一个或一组 json key (key path) 映射到一个或多个属性。如果一个属性没有映射关系，那默认会使用相同属性名作为映射。
在 json->model 的过程中：如果一个属性对应了多个 json key，那么转换过程会按顺序查找，并使用第一个不为空的值。
在 model->json 的过程中：如果一个属性对应了多个 json key (key path)，那么转换过程仅会处理第一个 json key (key path)；如果多个属性对应了同一个 json key，则转换过过程会使用其中任意一个不为空的值。
--------

### 3.Model 包含其他 Model

```
// JSON
{
    "author":{
        "name":"J.K.Rowling",
        "birthday":"1965-07-31T00:00:00+0000"
    },
    "name":"Harry Potter",
    "pages":256
}

// Model: 什么都不用做，转换会自动完成
@interface Author : NSObject
@property NSString *name;
@property NSDate *birthday;
@end
@implementation Author
@end

@interface Book : NSObject
@property NSString *name;
@property NSUInteger pages;
@property Author *author; //Book 包含 Author 属性
@end
@implementation Book
@end
```
--------

### 4.容器类属性

```
@class Shadow, Border, Attachment;

@interface Attributes
@property NSString *name;
@property NSArray *shadows; //Array<Shadow>
@property NSSet *borders; //Set<Border>
@property NSMutableDictionary *attachments; //Dict<NSString,Attachment>
@end

@implementation Attributes
// 返回容器类中的所需要存放的数据类型 (以 Class 或 Class Name 的形式)。
+ (NSDictionary *)modelContainerPropertyGenericClass {
    return @{@"shadows" : [Shadow class],
             @"borders" : Border.class,
             @"attachments" : @"Attachment" };
}
@end
```
在实际使用过过程中，`[Shadow class]`，`Border.class`，`@"Attachment"`没有明显的区别。
这里仅仅是创建作者有说明，实际使用时，需要对其遍历，取出容器中得字典，然后继续字典转模型。（****YYModel****的核心是通过****runtime****获取结构体中得****Ivars****的值，将此值定义为****key,****然后给****key****赋****value****值，所以我们需要自己遍历容器（****NSArray****，****NSSet****，****NSDictionary****），获取每一个值，然后****KVC****）。


--------

- 具体的代码实现如下：

```
NSDictionary *json =[self getJsonWithJsonName:@"ContainerModel"];
ContainerModel *containModel = [ContainerModel yy_modelWithDictionary:json];
NSDictionary *dataDict = [containModel valueForKey:@"data"];
//定义数组，接受key为list的数组
self.listArray = [dataDict valueForKey:@"list"]; 
 //遍历数组
[self.listArray enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        NSDictionary *listDict = obj;
        //获取数组中得字典
        List *listModel = [List yy_modelWithDictionary:listDict];
        //获取count 和 id
        NSString *count = [listModel valueForKey:@"count"];
        NSString *id = [listModel valueForKey:@"id"];
       
```
--------

### 5.黑名单与白名单

```
@interface User
@property NSString *name;
@property NSUInteger age;
@end

@implementation Attributes
// 如果实现了该方法，则处理过程中会忽略该列表内的所有属性
+ (NSArray *)modelPropertyBlacklist {
    return @[@"test1", @"test2"];
}
// 如果实现了该方法，则处理过程中不会处理该列表外的属性。
+ (NSArray *)modelPropertyWhitelist {
    return @[@"name"];
}
@end
```

--------

### 6.数据校验与自定义转换
实际这个分类的目的比较简单和明确。
就是对判断是否为时间戳，然后对时间戳进行处理，调用
`_createdAt = [NSDate dateWithTimeIntervalSince1970:timestamp.floatValue];`
获取时间。

```
// JSON:
{
    "name":"Harry",
    "timestamp" : 1445534567     //时间戳
}

// Model:
@interface User
@property NSString *name;
@property NSDate *createdAt;
@end

@implementation User
// 当 JSON 转为 Model 完成后，该方法会被调用。
// 你可以在这里对数据进行校验，如果校验不通过，可以返回 NO，则该 Model 会被忽略。
// 你也可以在这里做一些自动转换不能完成的工作。
- (BOOL)modelCustomTransformFromDictionary:(NSDictionary *)dic {
    NSNumber *timestamp = dic[@"timestamp"];
    if (![timestamp isKindOfClass:[NSNumber class]]) return NO;
    _createdAt = [NSDate dateWithTimeIntervalSince1970:timestamp.floatValue];
    return YES;
}

// 当 Model 转为 JSON 完成后，该方法会被调用。
// 你可以在这里对数据进行校验，如果校验不通过，可以返回 NO，则该 Model 会被忽略。
// 你也可以在这里做一些自动转换不能完成的工作。
- (BOOL)modelCustomTransformToDictionary:(NSMutableDictionary *)dic {
    if (!_createdAt) return NO;
    dic[@"timestamp"] = @(n.timeIntervalSince1970);
    return YES;
}
@end
```

> - 需要注意的时，如果用插件，对时间戳类型或默认创建为NSUInteger类型，需要将其更改为NSDate类型。

--------

### 7.Coding/Copying/hash/equal/description
以下方法都是YYModel的简单封装，实际使用过程和系统方法区别不大。对其感兴趣的可以点进方法内部查看。

```
@interface YYShadow :NSObject <NSCoding, NSCopying>
@property (nonatomic, copy) NSString *name;
@property (nonatomic, assign) CGSize size;
@end

@implementation YYShadow
// 直接添加以下代码即可自动完成
- (void)encodeWithCoder:(NSCoder *)aCoder { 
 [self yy_modelEncodeWithCoder:aCoder]; 
}
- (id)initWithCoder:(NSCoder *)aDecoder {
  self = [super init];
  return [self yy_modelInitWithCoder:aDecoder]; 
}
- (id)copyWithZone:(NSZone *)zone { 
 return [self yy_modelCopy]; 
}
- (NSUInteger)hash { 
 return [self yy_modelHash]; 
}
- (BOOL)isEqual:(id)object { 
 return [self yy_modelIsEqual:object]; 
}
- (NSString *)description { 
 return [self yy_modelDescription]; 
}
@end
```
--------


## 二、ESJsonFormat与YYModel的结合使用
**彩蛋**
给大家介绍一款插件，配合[ESJsonFormat](https://github.com/EnjoySR/ESJsonFormat-Xcode)



配图：
![ESJsonFormat插件使用.gif](http://upload-images.jianshu.io/upload_images/1467716-5c961bc376c72984.gif?imageMogr2/auto-orient/strip)


使用方法：
快捷键：`shift + control + J `
插件安装方法比较简单，在此不赘述，不知道可自行google。

**好处**：
> - 1. 可以直接将json数据复制，ESJsonFormat会根据数据类型自动生成属性。（建议还是要自行检查，比如时间戳，系统会默认帮你生成为NSUInteger，而我们想要的为NSDate类型）
> - 2. 对于多模型嵌套，不必创建多个文件，ESJsonFormat会自动在一个文件下创建多重类型,极其便捷。


至此YYModel的使用已讲解完毕，关于YYModel的底层核心是`运用runtime获取类结构体中Ivars，进行KVC操作，然后根据不同情况进行分别处理`。
此处只是传递给大家一个概念，不展开讲解，网上有很多源码分析文章，可自学google学习。
文末，做个综述。
建议大家有时间一定要多看底层，分析源码。不要只会用，知其然不知其所以然。
如有错误欢迎指出。

##写在最后
我得写作原则：
在技术学习道路上，阅读量和代码量绝不能线性提升你的技术水平。
同样写文章也是如此，作者所写的文章完全是基于自己对技术的理解，在写作时也力求形象不抽象。绝不copy充数，所以也欢迎大家关注和参与讨论。
技术学习绝不能孤胆英雄独闯天涯，而应在一群人的交流碰撞，享受智慧火花的狂欢。
希望我的文章能成为你的盛宴，也渴望你的建议能成为我的大餐。
如有错误请留言指正，对文章感兴趣可以关注作者不定期更新，也可微信`bin5211bin`。
