#
# Be sure to run `pod lib lint CreditCardForm.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = "CreditCardForm"
  s.version          = "0.1.0"
  s.summary          = "A ready-made card form UI that can be included in your iOS app, making it easy to accept credit and debit cards."

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!
  s.description      = <<-DESC
iOS Credit Card Form is a ready-made card form UI that can be included in your app, making it easy to accept credit and debit cards.
                       DESC

  s.homepage         = "https://github.com/braintree/ios-credit-card-form"
  # s.screenshots     = "www.example.com/screenshots_1", "www.example.com/screenshots_2"
  s.license          = 'MIT'
  s.author           = { "Elliot Lee" => "elliot.lee@getbraintree.com" }
  s.source           = { :git => "https://github.com/<GITHUB_USERNAME>/CreditCardForm.git", :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.platform     = :ios, '7.0'
  s.requires_arc = true

  s.source_files = 'CardForm/**/*.{h,m}'
  s.resource_bundles = {
    'CreditCardForm' => ['CardForm/Localization/*.lproj']
  }

  # s.public_header_files = 'CardForm/Classes/**/*.h'
  # s.frameworks = 'UIKit', 'MapKit'
  # s.dependency 'AFNetworking', '~> 2.3'
end
