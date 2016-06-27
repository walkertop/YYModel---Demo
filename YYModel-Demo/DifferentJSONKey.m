//
//  DifferentJSONKey.m
//  Demo-YYModel
//
//  Created by 郭彬 on 16/6/20.
//  Copyright © 2016年 walker. All rights reserved.
//

#import "DifferentJSONKey.h"

@implementation DifferentJSONKey

+ (NSDictionary *) modelCustomPropertyMapper {
    return @{@"UserID" : @"user_id",
             @"createdTime" : @"created_at"
             };
}

@end
