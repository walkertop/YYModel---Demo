//
//  YGXModel.m
//  Demo-YYModel
//
//  Created by 郭彬 on 16/6/20.
//  Copyright © 2016年 walker. All rights reserved.
//

#import "YGXModel.h"


@implementation YGXModel

+ (NSDictionary *)modelCustomPropertyMapper {
    return @{@"errnoInteger" : @"errno"
             };
}

+ (NSDictionary *)modelContainerPropertyGenericClass {
    return @{
             @"data" : [DataModel class]
             };
}

@end
