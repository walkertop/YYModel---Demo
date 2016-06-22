//
//  DataModel.m
//  Demo-YYModel
//
//  Created by 郭彬 on 16/6/20.
//  Copyright © 2016年 walker. All rights reserved.
//

#import "DataModel.h"

@implementation DataModel

+ (NSDictionary *)modelContainerPropertyGenericClass {
    return @{
             @"list" : [ListModel class],
             @"latest_expire_bonus" : [latestExpireBonusModel class]
             };
}

@end
