<?php

/**
 * @file
 */
?>
<style type="text/css">
    h4.inline {
        display: inline-block;
        margin-right: 5px;
    }
    pre {
        background: #f9f9f9;
        border: 1px solid rgba(0,0,0,.15);
        padding: 10px;
        border-radius: 5px;
    }
    pre.nowrap {
        white-space: nowrap;
    }
</style>

<h2>Epsilon Log Details: <?php echo $log_id; ?></h2>
<div>
    <h4 class="inline">Date:</h4><?php echo date("d/m/y h:i:sa", $created); ?>
</div>
<div>
    <h4>Requestor:</h4>
    <pre class="nowrap">
        <?php echo $user->name; ?>
    </pre>
</div>
<div>
    <h4>Endpoint:</h4>
    <pre class="nowrap">
        <?php echo $endpoint; ?>
    </pre>
</div>
<div>
    <h4>Status Code:</h4>
    <pre class="nowrap">
        <?php echo $status_code; ?>
    </pre>
</div>
<div>
    <h4>Status Message:</h4>
    <pre class="nowrap">
        <?php echo $status_message; ?>
    </pre>
</div>
<div>
    <h4>Header:</h4>
    <pre>
        <?php print_r($header); ?>
    </pre>
</div>
<div>
    <h4>Request:</h4>
    <pre class="nowrap">
        <?php print_r($request); ?>
    </pre>
</div>
<div>
    <h4>Response:</h4>
    <pre>
        <?php print_r($response); ?>
    </pre>
</div>

<a href="/admin/config/services/epsilon_harmony/logs">Go Back</a>
