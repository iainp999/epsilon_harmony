
# Epsilon Harmony Documentation

Follow the below procedure to install and use the Epsilon Harmony Client module for Drupal 7.

## Installation

 - Download the module from https://www.drupal.org/project/epsilon_harmony
 - Copy the module content in `/sites/all/modules` directory in your Drupal installation.
 - Enable the module from `/admin/modules`.

## Configuration

 - Go to `/admin/config/services/epsilon_harmony/configurations` and fill in all the required fields.
 - To add multiple message ID's from Epsilon -- API navigate to `/admin/config/services/epsilon_harmony/message_configuration` and add the desired message identifier along with the message ID received from the Epsilon Team.

## Usage

In order to use the module, just pass the data to desired method, more of this is explained below.
##### Please use the following code to call the API.
```
<?php
	use Drupal\epsilon_harmony\EpsilonApiFactory;
	$classObj = new EpsilonApiFactory;
?>
```

### Method 1 (Create Record)
To create a record pass the desired attributes in a key=>value pair.
```
<?php
	use Drupal\epsilon_harmony\EpsilonApiFactory;
	$classObj = new EpsilonApiFactory;
	
	$record = [];
	$record['CustomerKey'] = "<CustomerKey>";
	$record['FirstName'] = "<Firstname>";
	$record['LastName'] = "<Lastname>";
	$record['PreferredChannel'] = "<PreferredChannel>";
	$record['GlobalOptOutFlag'] = "<GlobalOptOutFlag>";
	$record['AddressLine1'] = "<AddressLine1>";
	...etc
	$classObj->createRecord($record);
?>
*Note* In the above request only "CustomerKey" is a mandatory attribute rest can be removed.
```
### Method 2 (Update Record)
To update a record pass the desired attributes in a key=>value pair.
```
<?php
	use Drupal\epsilon_harmony\EpsilonApiFactory;
	$classObj = new EpsilonApiFactory;
	
	$record = [];
	$record['CustomerKey'] = "<CustomerKey>";
	$record['FirstName'] = "<Firstname>";
	$record['LastName'] = "<Lastname>";
	$record['PreferredChannel'] = "<PreferredChannel>";
	$record['GlobalOptOutFlag'] = "<GlobalOptOutFlag>";
	$record['AddressLine1'] = "<AddressLine1>";
	...etc
	$classObj->updateRecord($record);
?>
*Note* In the above request only "CustomerKey" is a mandatory attribute rest can be removed.
```
### Method 3 (Send a Message)
To send a Email via Epsilon Harmony first add the desired message key(received) from Epsilon in the `admin/config/services/epsilon_harmony/message_configuration`.
In the above form you can add multiple message ID's and trigger the API by passing the respective message identifier.
```
<?php
	use Drupal\epsilon_harmony\EpsilonApiFactory;
	$classObj = new EpsilonApiFactory;
	
	$record = [];
	$record['subjectOverride'] = "<Override if necessary not a required attribute>";
	$record['recipients'][] = array(
		"customerKey" => "<CustomerKey>",
		"emailAddress" => "<Email ID>",
		'attributes' => [
			array(
				'attributeName' => "FIRST_NAME",
				'attributeType' => "String",
				'attributeValue' => "<FirstName>",
			),
			array(
				'attributeName' => "LAST_NAME",
				'attributeType' => "String",
				'attributeValue' => "<LastName>",
			)
			...etc
		]
	);
	$classObj->sendMessage("<message-identifier>", $record);
?>
*Note* In the above request only "customerKey" and "emailAddress" are mandatory attributes rest can be removed.
```
## Logging
All the API triggers are logged in `admin/config/services/epsilon_harmony/logs` which can be used for debugging purpose.
