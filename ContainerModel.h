//
//  ContainerModel.h
//  YYModel-Demo
//
//  Created by 郭彬 on 16/6/22.
//  Copyright © 2016年 walker. All rights reserved.
//

#import <Foundation/Foundation.h>

@class Data,Latest_Expire_Bonus,List;
@interface ContainerModel : NSObject

@property (nonatomic, assign) NSInteger errnoInteger;

@property (nonatomic, strong) Data *data;

@property (nonatomic, copy) NSString *error;

@end
@interface Data : NSObject

@property (nonatomic, copy) NSString *count;

@property (nonatomic, strong) Latest_Expire_Bonus *latest_expire_bonus;

@property (nonatomic, strong) NSArray<List *> *list;

@end

@interface Latest_Expire_Bonus : NSObject

@property (nonatomic, copy) NSString *minutes;

@property (nonatomic, copy) NSString *money;

@end

@interface List : NSObject

@property (nonatomic, copy) NSString *id;

@property (nonatomic, copy) NSString *expiredAt;

@property (nonatomic, copy) NSString *count;

@property (nonatomic, assign) NSInteger flag;

@property (nonatomic, assign) NSInteger leftNum;

@property (nonatomic, copy) NSString *usedNum;

@property (nonatomic, copy) NSString *createdAt;

@property (nonatomic, copy) NSString *sendNum;

@end

