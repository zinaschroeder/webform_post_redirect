<?php

    /**
     * @file
     *     Webform Post Redirect module page functions.
     */

    /**
     * Callback function for redirection page.
     */
    function webform_post_redirect_page($nid, $sid) {

        global $base_url;

        // Add forced form submission redirect script
        drupal_add_js(drupal_get_path('module', 'webform_post_redirect') 
            . '/js/webform_post_redirect-page.js');

        // Basic page content 
        $output = '<h1>Redirecting</h1><img src="' . $base_url . '/' 
                . drupal_get_path('module', 'webform_post_redirect') 
                . '/images/loading.gif" class="centered" /><br/><p>If your browser does 
                not automatically redirect you in 5 seconds, please click the button below.</p>'; // TODO add admin interface to customize page content

        // Get hidden form
        $form = drupal_get_form('webform_post_redirect_hidden_form', $nid, $sid);

        $output .= drupal_render($form);

        return $output;
    }

    /**
     * Generates the hidden form on the redirect page.
     */
    function webform_post_redirect_hidden_form($form_id, &$form_state, $nid, $sid) {

        $form = array();

        include_once(drupal_get_path('module', 'webform') . "/includes/webform.submissions.inc");

        $node         = node_load($nid);
        $post         = webform_post_redirect_load($nid);
        $submission   = webform_get_submission($nid, $sid);

        $redirect_url = $node->webform['redirect_url'];
        $components   = $node->webform['components'];

        if (strpos($post['included_components'], ', ') !== FALSE) {
            $included_components = explode(', ', $post['included_components']);
        } 
        else {
            $included_components = array($post['included_components']);
        }

        $form['#id']     = 'post_redirect_form';
        $form['#action'] = $redirect_url;
        $form['#method'] = 'POST';

        // Create hidden input for each included component
        foreach ($included_components as $component) {

            $value = array_shift($submission->data[$component]);

            // That value isn't empty or make sure that empty fields are not exluded
            if (!empty($value) || $post['exclude_empty'] == 0) {
                $form[$components[$component]['form_key']] = array(
                    '#type'  => 'hidden',
                    '#value' => $value,
                );
            }
        }

        $form['submit_button'] = array(
            '#type'       => 'button',
            '#value'      => 'Redirect Now', // TODO add admin interface to customize button text
            '#attributes' => array(
                'class'   => array('centered')
            ),
        );

        return $form;
    }