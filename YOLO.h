#import <Foundation/Foundation.h>



@interface NSArray (RubyEnumerable)

/**
 A notable difference between our map and Ruby’s is if you return nil in your
 block, we skip that element. It’s as though compact is run afterwards. The
 reason for this is:
   1) nil cannot be added to NSArray;
   2) objc is awesome because calling a method on nil is not an error, so if we
      *could* add nil to arrays it would be the same effect as not having that
      element in (mostly).
   3) If we added NSNull instead you'd *continuously have to check for NSNull
      everywhere and we have made the decision that this would be super lame.
**/
- (NSArray *(^)(id (^)(id o)))map;

- (NSArray *(^)(BOOL (^)(id o)))select;
- (NSArray *(^)(BOOL (^)(id o)))reject;
- (NSArray *(^)(void (^)(id o)))each;
- (NSArray *(^)(void (^)(id o, uint index)))eachWithIndex;

/**
 Combines all elements into a single value. Memo starts as the first element in
 the array and each iteration is the value returned from your block
**/
- (id(^)(id (^)(id memo, id obj)))reduce;

/**
 Same as reduce, but you specify the initial memo, usually used to populate eg.
 an NSDictionary by providing an initial memo of @{} though with experience
 there are often better ways to do such things, like eg. group_by
**/
- (id(^)(id initial_memo, id (^)(id memo, id obj)))inject;

- (NSArray *)flatten;
- (id(^)(NSInteger (^)(id)))min;
- (id(^)(NSInteger (^)(id)))max;
- (id(^)(BOOL (^)(id o)))find;
- (NSUInteger (^)(id obj))indexOf;
- (NSArray *(^)(NSArray *(^)(id o)))flatMap;
- (NSDictionary *(^)(id (^)(id o)))groupBy;

/**
 Accepts a block or a string being a keypath, though
 we feed the keypath to a NSSortDescriptor, so you
 can't use dots in there.
**/
- (NSArray *(^)(id (^)(id o)))sortBy;
- (NSArray *)sort;

@end



@interface NSArray (Underscore)
/**
 Map for the specified keypath, uses valueForKeyPath so you can specify
 multiple levels of key. Check Apple’s docs if you are unfamiliar.
 You can also pass Classes eg: array.pluck(NSNumber.class)
**/
- (NSArray *(^)(id keypathOrClass))pluck;
@end



@interface NSArray (Ruby)

- (NSArray *)uniq;  // like Ruby, preserves sort order

- (NSArray *(^)(NSArray *other_array))concat;

/**
 Ruby allows ranges to be passed to slice, but since we have no equivalent I
 have made it so length (as well as start) can be negative, in that case length
 is no longer length, but end-position.
 **/
- (NSArray *(^)(int start, int length))slice;

- (NSArray *(^)(uint))first;
- (NSArray *(^)(uint))last;

/**
 NOTE we didn't implement take as its name is confusing and it behaves the exact
 same as first().
**/

- (NSArray *)reverse;
- (NSString *)join;
- (NSArray *)transpose;
- (NSArray *)shuffle;

/**
 Returns a random object from the array.
**/
- (id)sample;

/**
 Returns a new array by rotating self so that the element at count is the first
 element of the new array. If count is negative then it rotates in the opposite
 direction, starting from the end of self where -1 is the last element.
**/
- (NSArray *(^)(int))rotate;

@end



@interface NSArray (YOLO)

- (NSArray *(^)(id arrayOrSetOrObject))without;
- (NSSet *)set;

/**
 Parallel map. Obviously: be thread safe in your block. Doesn't return
 until everything is done. Typically not worth using unless you have
 large lists since the overhead of thread-syncronization may be greater
 than the parallel savings otherwise.
**/
- (NSArray *(^)(id (^)(id o)))pmap;

/**
 Chosen over isempty because almost always we use this in an if statement and in
 that context: `if (array.empty) {}` the code is clear.
**/
- (BOOL)empty;

@end



@interface NSMutableArray (YOLO)

- (id)pop;
- (NSMutableArray *(^)(id obj))push;

- (id)shift;
- (NSMutableArray *(^)(id obj))unshift;

@end



@interface NSSet (YOLO)

- (NSSet *)without:(NSSet *)set;

@end



@interface NSSet (RubyEnumerable)

- (NSSet *(^)(void (^)(id o)))each;

@end



@interface NSDictionary (Underscore)

/** two forms supported, single argument which is a dictionary
  * or *two* arguments, a key and value */
- (NSDictionary *(^)(id o, ...))extend;

@end



@interface NSDictionary (YOLO)

/**
 because [] syntax is often ugly when chaining
**/
- (id (^)(id))get;

@end



@interface NSNumber (Ruby)

- (NSArray *(^)(int))upto;

@end



@interface NSString (YOLO)

- (NSArray *(^)(NSString *))split;

@end
