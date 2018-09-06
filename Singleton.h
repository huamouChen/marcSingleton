// 宏只是起到一个替换的作用，不会检查错误，所以检查宏是否正确的时候，把宏的定义代码粘贴到使用的地方替换即可

// 宏中 ## 用于拼接字符串
#define singletonInterface(className)    + (instancetype)share##className;

#if __has_feature(objc_arc)  // 判断是否是 ARC 环境
// 宏中 \ 用于拼接较长的字符串
#define singletonImplementatio(className) \
static id instance;\
+ (instancetype)allocWithZone:(struct _NSZone *)zone {\
    static dispatch_once_t onceToken;\
    dispatch_once(&onceToken, ^{\
        instance = [super allocWithZone:zone];\
    });\
    return instance;\
}\
+ (instancetype)share##className {\
    static dispatch_once_t onceToken;\
    dispatch_once(&onceToken, ^{\
        instance = [[self alloc] init];\
    });\
    return instance;\
}\
- (id)copyWithZone:(NSZone *)zone {\
    return instance;\
}

#else

#define singletonImplementatio(className) \
static id instance;\
+ (instancetype)allocWithZone:(struct _NSZone *)zone {\
    static dispatch_once_t onceToken;\
    dispatch_once(&onceToken, ^{\
        instance = [super allocWithZone:zone];\
    });\
    return instance;\
}\
+ (instancetype)share##className {\
    static dispatch_once_t onceToken;\
    dispatch_once(&onceToken, ^{\
        instance = [[self alloc] init];\
    });\
    return instance;\
}\
- (id)copyWithZone:(NSZone *)zone {\
    return instance;\
}\
- (oneway void)release {}\
- (instancetype)retain {return instance;}\
- (instancetype)autorelease {return instance;}\
- (NSUInteger)retainCount {return ULONG_LONG_MAX;}
#endif


