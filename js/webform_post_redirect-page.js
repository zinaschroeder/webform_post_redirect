/**
 * @file
 * Force submission of form on load to trigger POST redirect
 */

Drupal.behaviors.webform_post_redirect_submit_form = {
  attach: function (context, settings) {
    $('form#webform_post_redirect_form').submit();
  }
};
