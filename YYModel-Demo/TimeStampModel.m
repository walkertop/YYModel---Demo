//
//  TimeStampModel.m
//  YYModel-Demo
//
//  Created by 郭彬 on 16/6/27.
//  Copyright © 2016年 walker. All rights reserved.
//

#import "TimeStampModel.h"

@implementation TimeStampModel

- (BOOL)modelCustomTransformFromDictionary:(NSDictionary *)dic {
    NSNumber *timestamp = dic[@"timestamp"];
    if (![timestamp isKindOfClass:[NSNumber class]]) return NO;
    _createdAt = [NSDate dateWithTimeIntervalSince1970:timestamp.floatValue];
    return YES;
}

//- (BOOL)modelCustomTransformToDictionary:(NSMutableDictionary *)dic {
//    if (!_createdAt) return NO;
//    dic[@"timestamp"] = @(n.timeIntervalSince1970);
//    return YES;
//}
@end
