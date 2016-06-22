//
//  DataModel.h
//  Demo-YYModel
//
//  Created by 郭彬 on 16/6/20.
//  Copyright © 2016年 walker. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ListModel.h"
#import "YYModel.h"
#import "latestExpireBonusModel.h"

@class latestExpireBonusModel,ListModel;

@interface DataModel : NSObject

//@property(nonatomic,strong) ListModel *model;
//@property(nonatomic,strong) NSDictionary *bonus_statics;

@property(nonatomic,assign) NSInteger count;
@property(nonatomic,strong) NSDictionary *latest_expire_bonus;
@property(nonatomic,strong) NSArray<ListModel *> *list;

@end

