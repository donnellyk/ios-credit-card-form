#import <UIKit/UIKit.h>

#import "BTDropInErrorAlert.h"
#import "BTDropInLocalizedString.h"

@interface BTDropInErrorAlert () <UIAlertViewDelegate>

@property (nonatomic, copy) void (^retryBlock)(void);

@property (nonatomic, copy) void (^cancelBlock)(void);

@end

@implementation BTDropInErrorAlert

- (instancetype)initWithCancel:(void (^)(void))cancelBlock retry:(void (^)(void))retryBlock {
    self = [super init];
    if (self) {
        self.retryBlock = retryBlock;
        self.cancelBlock = cancelBlock;
    }
    return self;
}


- (void)show {
    NSString *localizedOK = BTDropInLocalizedString(ERROR_ALERT_OK_BUTTON_TEXT);
    NSString *localizedCancel = BTDropInLocalizedString(ERROR_ALERT_CANCEL_BUTTON_TEXT);

    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:self.title
                                                        message:self.message
                                                       delegate:self
                                              cancelButtonTitle:self.retryBlock ? localizedCancel : localizedOK
                                 otherButtonTitles:nil];

    if (self.retryBlock) {
        NSString *localizedTryAgain = BTDropInLocalizedString(ERROR_ALERT_TRY_AGAIN_BUTTON_TEXT);
        [alertView addButtonWithTitle:localizedTryAgain];

    }

    [alertView show];
}

- (void)alertView:(__unused UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == 0 && self.cancelBlock) {
        self.cancelBlock();
    } else if (buttonIndex == 1 && self.retryBlock) {
        self.retryBlock();
    }
}

- (NSString *)title {
    NSString *localizedConnectionError = BTDropInLocalizedString(ERROR_ALERT_CONNECTION_ERROR);

    return _title ?: localizedConnectionError;
}

@end
