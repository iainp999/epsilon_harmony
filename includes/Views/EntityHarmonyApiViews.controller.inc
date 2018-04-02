<?php

/**
 * EntitySSLFiles Views Controller class.
 */
class EntityEpsilonHarmonyLogsViewsController extends EntityDefaultViewsController {

  /**
   * Edit or add extra fields to views_data().
   */
  public function views_data() {
    $data = parent::views_data();
    $data['epsilon_harmony_logs']['created']['field']['handler'] = 'views_handler_field_date';
    $data['epsilon_harmony_logs']['uid'] = array(
      'title' => t('User'),
      'help' => t('Relate a user who created it.'),
      'relationship' => array(
        'handler' => 'views_handler_relationship',
        'base' => 'users',
        'base field' => 'uid',
        'field' => 'uid',
        'field_name' => 'uid',
        'label' => t('user'),
      ),
    );
    return $data;
  }

}
