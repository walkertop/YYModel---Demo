//
//  Blacklist&Whitelist.h
//  Demo-YYModel
//
//  Created by 郭彬 on 16/6/20.
//  Copyright © 2016年 walker. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "YYModel.h"

@interface BlacklistAndWhitelist : NSObject

@property (nonatomic, assign) NSInteger uid;
@property (nonatomic,copy) NSString *name;
@property (nonatomic,copy) NSDate *created;

@end
