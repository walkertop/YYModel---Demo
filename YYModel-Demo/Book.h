//
//  Book.h
//  Demo-YYModel
//
//  Created by 郭彬 on 16/6/20.
//  Copyright © 2016年 walker. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Author.h"
#import "YYModel.h"



@interface Book : NSObject

@property(nonatomic,copy)NSString *name;
@property(nonatomic,assign)NSUInteger pages;
@property Author *author; //Book 包含 Author 属性
//更改之后的name
//@property(nonatomic,strong)NSString *namePlus;

@end
