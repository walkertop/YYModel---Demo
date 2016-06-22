//
//  Blacklist&Whitelist.m
//  Demo-YYModel
//
//  Created by 郭彬 on 16/6/20.
//  Copyright © 2016年 walker. All rights reserved.
//

#import "BlacklistAndWhitelist.h"

@implementation BlacklistAndWhitelist

+ (NSArray *)modelPropertyWhitelist {
    return @[@"name"];
}
//+ (NSArray *)modelPropertyBlacklist {
//    return @[@"uid"];
//}
@end
