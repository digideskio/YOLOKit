#import "NSArray+transpose.h"
#import "YOLO.ph"

@implementation NSArray (YOLODict)

- (NSDictionary *)dict {
    NSArray *aa = self.transpose;
    if (aa.count <= 1)
        return @{};
    return [NSDictionary dictionaryWithObjects:aa[1] forKeys:aa[0]];
}

@end
