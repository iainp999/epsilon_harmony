<?php

/**
 * @file
 * The controller for the epsilon_harmony_logs entity containing the CRUD operations.
 */

/**
 * The controller class for ssfiles contains methods for the product CRUD operations.
 *
 * Mainly relies on the EntityAPIController class provided by the Entity
 * module, just overrides specific features.
 */
class EntityEpsilonHarmonyLogsController extends EntityAPIController {

  /**
   * Override save method.
   *
   * Populate created and updated dates automatically.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    global $user;

    // Update time.
    if (isset($entity->is_new)) {
      $entity->created = REQUEST_TIME;
    }

    return parent::save($entity, $transaction);
  }

}

/**
 * Our custom entity class.
 *
 * The Entity class we're overriding is in
 * sites/all/modules/contrib/entity/includes/entity.inc.
 */
class EpsilonHarmonyLog extends Entity {

}
