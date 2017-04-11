<?php

  /**
   * @file
   *   Webform Post Redirect module page functions.
   */

  /**
   * Callback function for redirection page.
   */
  function webform_post_redirect_page($nid, $sid) {

    global $base_url;

    $redirect = webform_post_redirect_load($nid);
    $defaults = webform_post_redirect_get_page_defaults();

    // Set message to default if blank
    $message  = t(!empty($redirect['message']) ? $redirect['message'] : '<p>' . $defaults['message'] . '<p>');

    $page = array(
      '#theme'      => 'webform_post_redirect_page',
      '#page_title' => t(!empty($redirect['page_title']) ? $redirect['page_title'] : $defaults['page_title']),
      '#message'    => check_markup($message, $redirect['message_format']),
      '#form'       => drupal_get_form('webform_post_redirect_hidden_form', $nid, $sid),
    );

    $page['#attached']['js'][] = array('data' => drupal_get_path('module', 'webform_post_redirect') . '/js/webform_post_redirect-page.js');

    return $page;
  }

  /**
   * Generates the hidden form on the redirect page.
   */
  function webform_post_redirect_hidden_form($form_id, &$form_state, $nid, $sid) {

    $form = array();

    include_once(drupal_get_path('module', 'webform') . "/includes/webform.submissions.inc");

    $node       = node_load($nid);
    $redirect   = webform_post_redirect_load($nid);
    $submission = webform_get_submission($nid, $sid);
    $defaults   = webform_post_redirect_get_page_defaults();

    $redirect_url = $node->webform['redirect_url'];
    $components   = $node->webform['components'];

    if (strpos($redirect['included_components'], ', ') !== FALSE) {
      $included_components = explode(', ', $redirect['included_components']);

    } else {
      $included_components = array($redirect['included_components']);
    }

    $form['#id']     = 'post_redirect_form';
    $form['#action'] = $redirect_url;
    $form['#method'] = 'POST';

    // Create hidden input for each included component
    foreach ($included_components as $component) {

      // Check that component value exists
      if (!empty($submission->data[$component])) {

        // If component has multiple values, pass them along as JSON data
        if (is_array($submission->data[$component]) && sizeof($submission->data[$component]) > 1) {

          switch ($redirect['multivalue_format']) {

            case 'serialize':
              $value = serialize($submission->data[$component]);
              break;

            case 'json':
            default:
              $value = json_encode($submission->data[$component]);
              break;
          }

        } else {
          $value = array_shift($submission->data[$component]);
        }

      } else {
        $value = "";
      }

      // That value isn't empty or make sure that empty fields are not excluded
      if (!empty($value) || $redirect['exclude_empty'] == 0) {

        // Create hidden form element to pass on field value
        $form[$components[$component]['form_key']] = array(
          '#type'  => 'hidden',
          '#value' => $value,
        );
      }
    }

    $form['submit_button'] = array(
      '#type'       => 'button',
      '#value'      => t(!empty($redirect['button_text']) ? $redirect['button_text'] : $defaults['button_text']),
      '#attributes' => array(
        'class' => array('centered')
      ),
    );

    return $form;
  }