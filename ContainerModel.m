//
//  ContainerModel.m
//  YYModel-Demo
//
//  Created by 郭彬 on 16/6/22.
//  Copyright © 2016年 walker. All rights reserved.
//

#import "ContainerModel.h"

@implementation ContainerModel
+ (NSDictionary *) modelCustomPropertyMapper {
    return @{@"errnoInteger" : @"errno"
             };
}

@end
@implementation Data

+ (NSDictionary *)objectClassInArray{
    return @{@"list" : [List class]};
}

@end


@implementation Latest_Expire_Bonus

@end


@implementation List

@end


