<?php

if (extension_loaded("s2go")) {
	$lat = 31.263104;
	$lng = 121.473567;
	$cellid = s2go_cellid($lat, $lng);
	var_dump($cellid);
        $cellids = s2go_getcoving($lat, $lng, 2000.0, 256);
        $data = json_decode($cellids, true);
	print_r($data);
}
