/**
 * @file
 * Improvements to webform settings interface.
 */

jQuery(document).ready(function($){

    // Start in correct toggle display
    togglePostRedirectElement($('#edit-redirect input:checked').val(), 'url', '.form-item-redirect-post');
    togglePostRedirectElement($('#edit-redirect-post').is(':checked'), true, '#edit-components.webform-component-select-table');

    // When the radio changes, check if the checkbox and components should be hidden
    $('#edit-redirect input').on('change', function() {

        if ($(this).val() == 'url') {
            $('.form-item-redirect-post').show();

            if ($('#edit-redirect-post').is(':checked')) {
                $('#edit-components.webform-component-select-table').show();
            } else {
                $('#edit-components.webform-component-select-table').hide();
            }
        } else {
            $('.form-item-redirect-post').hide();
            $('#edit-components.webform-component-select-table').hide();
        }
    });

    // When the checkbox changes, check if components should be hidden
    $('#edit-redirect-post').on('change', function() {
        togglePostRedirectElement($(this).is(':checked'), true, '#edit-components.webform-component-select-table');
    });

    // Trigger display of element based on trigger and truth case
    function togglePostRedirectElement(trigger, showCase, element) {
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