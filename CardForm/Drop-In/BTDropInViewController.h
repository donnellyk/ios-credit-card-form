#import <UIKit/UIKit.h>
#import "BraintreeCore.h"

@class BTUI;
@protocol BTDropInViewControllerDelegate;

/// A view controller that provides a quick and easy payment experience.
///
/// When initialized with a Braintree client, the Drop In will prompt a user for payment details,
/// based on your Gatweay configuration. The Drop In payment form supports cards and PayPal. When
/// using Drop In, you don't need to worry about which methods are already on file with Braintree;
/// newly created methods are saved as part of the Drop In flow as needed.
///
/// Upon successful form submission, you will receive a payment method nonce, which you can
/// transact with on your server. Client and validation errors are handled internally by Drop In;
/// other types of Errors are rare and generally irrecoverable.
///
/// The Drop In view controller delegates presentation and dismissal to the developer. It has been
/// most thoroughly tested in the context of a UINavigationController.
///
/// The Drop In can send success and cancelation messages to the developer via the
/// delegate. See `delegate` and `BTDropInViewControllerDelegate`.
///
/// You can customize Drop In in various ways, for example, you can change the primary Call To
/// Action button text. For visual customzation options see `theme` and `BTUI`. Like any
/// UIViewController, you can setup properties like `title` or `navigationBar.rightBarButtonItem`.
@interface BTDropInViewController : UIViewController

/// Initialize a new Drop In.
///
/// @param apiClient A Braintree API client
///
/// @return A new Drop In view controller that is ready to be presented.
- (instancetype)initWithAPIClient:(BTAPIClient *)apiClient;

/// The Braintree API client used for communication with Braintree servers. This property is exposed
/// to enable the use of other UIViewController initializers, e.g. when using Storyboards.
///
/// @see BTAPIClient
@property (nonatomic, strong) BTAPIClient *apiClient;

/// The array of `BTTokenized` payment information objects on file. The tokenized payment info may be in the Vault.
/// Most payment methods are automatically Vaulted if the client token was generated with a customer ID.
@property (nonatomic, strong) NSArray *paymentInfoObjects;

#pragma mark State Change Notifications

/// The delegate that, if set, is notified of success or failure.
@property (nonatomic, weak) id<BTDropInViewControllerDelegate> delegate;

#pragma mark Customization

/// The presentation theme to use for the Drop In.
@property (nonatomic, strong) BTUI *theme;

/// Primary text to display in the summary view.
///
/// Intended to provide a name the overall transaction taking place. For example, "1 Item", "1 Year Subscription", "Yellow T-Shirt", etc.
///
/// If summaryTitle or summaryDescription are nil, then the summary view is not shown.
@property (nonatomic, copy) NSString *summaryTitle;

/// Detail text to display in the summary view.
///
/// Intended to provide a few words of detail. For example, "Ships in Five Days", "15 feet by 12 feet" or "We know you'll love it"
///
/// If summaryTitle or summaryDescription are nil, then the summary view is not shown.
@property (nonatomic, copy) NSString *summaryDescription;

/// A string representation of the grand total amount
///
/// For example, "$12.95"
@property (nonatomic, copy) NSString *displayAmount;

/// The text to display in the primary call-to-action button. For example: "$19 - Purchase" or "Subscribe Now".
@property (nonatomic, copy) NSString *callToActionText;

/// Whether to hide the call to action control.
///
/// When true, a submit button will be added as a bar button item (which
/// relies on the drop-in view controller being embedded in a navigation controller.
///
/// Defaults to `NO`.
///
/// @see callToAction
/// @see callToActionAmount
@property (nonatomic, assign) BOOL shouldHideCallToAction;

/// Fetches the customer's saved payment methods and populates Drop In with them.
///
/// @note For the best user experience, you should call this method as early as
///       possible (after initializing BTDropInViewController, before presenting it)
///       in order to avoid a loading spinner.
- (void)fetchPaymentMethods;


@end

/// A protocol for BTDropInViewController completion notifications.
@protocol BTDropInViewControllerDelegate <NSObject>

/// Informs the delegate when the user has successfully provided payment info that has been
/// successfully tokenized.
///
/// Upon receiving this message, you should dismiss Drop In.
///
/// @param viewController The Drop In view controller informing its delegate of success
/// @param tokenization The selected (and possibly newly created) tokenized payment information.
- (void)dropInViewController:(BTDropInViewController *)viewController didSucceedWithTokenization:(id<BTTokenized>)tokenization;

/// Informs the delegate when the user has decided to cancel out of the Drop In payment form.
///
/// Drop In handles its own error cases, so this cancelation is user initiated and
/// irreversable. Upon receiving this message, you should dismiss Drop In.
///
/// @param viewController The Drop In view controller informing its delegate of failure.
/// @param error An error that describes the failure.
- (void)dropInViewControllerDidCancel:(BTDropInViewController *)viewController;

@optional

/// Informs the delegate when the user has entered or selected payment information.
///
/// @param viewController The Drop In view controller informing its delegate
- (void)dropInViewControllerWillComplete:(BTDropInViewController *)viewController;

@end
