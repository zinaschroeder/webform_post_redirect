/**
 * @file
 * Improvements to webform settings interface.
 */

jQuery(document).ready(function($){

  // Start in correct toggle display
  toggle_post_redirect_element($('#edit-redirect input:checked').val(), 'url', '.form-item-redirect-post');
  toggle_post_redirect_element($('#edit-redirect-post').is(':checked'), true, '#edit-components.webform-component-select-table');
  toggle_post_redirect_element($('#edit-redirect-post').is(':checked'), true, '#edit-page-settings');

  // When the radio changes, check if the checkbox and components should be hidden
  $('#edit-redirect input[type=radio]').on('change', function() {

    if ($(this).val() == 'url') {
      $('.form-item-redirect-post').show();

      if ($('#edit-redirect-post').is(':checked')) {
        $('#edit-components.webform-component-select-table').show();
        $('#edit-page-settings').show();
      } else {
        $('#edit-components.webform-component-select-table').hide();
        $('#edit-page-settings').hide();
      }
    } else {
      $('.form-item-redirect-post').hide();
      $('#edit-components.webform-component-select-table').hide();
      $('#edit-page-settings').hide();
    }
  });

  // When the checkbox changes, check if components should be hidden
  $('#edit-redirect-post').on('change', function() {
    toggle_post_redirect_element($(this).is(':checked'), true, '#edit-components.webform-component-select-table');
    toggle_post_redirect_element($('#edit-redirect-post').is(':checked'), true, '#edit-page-settings');
  });

  // Trigger display of element based on trigger and truth case
  function toggle_post_redirect_element(trigger, showCase, element) {
    switch(trigger) {
      case showCase:
        $(element).show();
        break;
      default:
        $(element).hide();
        break;
    }
  };
});