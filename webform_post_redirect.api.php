<?php

  /**
   * @file
   * Sample hooks demonstrating usage in Webform Post Redirect.
   */

  /**
   * Alter the list of components to exclude from Webform Post Redirect settings.
   */
  function hook_webform_post_redirect_excluded_components_alter(&$items) {

    // Date fields will no longer be available to send via redirected POST data
    $items[] = 'date';
  }