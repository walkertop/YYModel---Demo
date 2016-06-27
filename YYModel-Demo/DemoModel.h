//
//  DemoModel.h
//  YYModel-Demo
//
//  Created by 郭彬 on 16/6/27.
//  Copyright © 2016年 walker. All rights reserved.
//

#import <Foundation/Foundation.h>

//1, 创建一个集成自NSobject的DemoModel
//2, 使用快捷键进行操作
//3, 修改/不修改创建数据模型的名称
@class Author;
@interface DemoModel : NSObject

@property (nonatomic, copy) NSString *name;

@property (nonatomic, strong) Author *author;

@property (nonatomic, assign) NSInteger pages;

@end
@interface Author : NSObject

@property (nonatomic, copy) NSString *name;

@property (nonatomic, copy) NSString *birthday;

@end

