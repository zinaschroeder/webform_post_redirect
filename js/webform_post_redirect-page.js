/**
 * @file
 * Force submission of form on load to trigger POST redirect
 */

jQuery(document).ready(function($){

    function submit_form() {
        document.getElementById('post_redirect_form').submit();
    }

    window.onload = submit_form;

});