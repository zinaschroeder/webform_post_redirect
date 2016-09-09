/**
 * @file
 * Force submission of form on load to trigger POST redirect
 */

jQuery(document).ready(function($){

    function submitForm() {
        document.getElementById('post_redirect_form').submit();
    }

    window.onload = submitForm;

});