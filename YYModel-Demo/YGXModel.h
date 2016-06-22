//
//  YGXModel.h
//  Demo-YYModel
//
//  Created by 郭彬 on 16/6/20.
//  Copyright © 2016年 walker. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DataModel.h"
#import "YYModel.h"


@interface YGXModel : NSObject

@property(nonatomic, strong) NSDictionary *data;
@property(nonatomic, copy) NSString *error;
@property(nonatomic, assign) NSInteger errnoInteger;

@end
