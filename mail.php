<?php
require _DIR_ . '/vendor/autoload.php';
use PHPMailer\PHPMailer\PHPMailer;
use PHPMailer\PHPMailer\Exception;
$mail = new PHPMailer(); $mail->IsSMTP(); $mail->Mailer =
"smtp";
$mail->SMTPDebug = 1;
$mail->SMTPAuth = TRUE;
$mail->SMTPSecure = "tls";
$mail->Port = 587;
$mail->Host = "smtp.gmail.com";
$mail->Username = "brahamanyanupur@gmail.com";
$mail->Password = "uvrflvtsnwcxrocc";
while(True){
// Fetch data from server
$channel_id = 2287037;
$field_id = 1;
$format = 'xml';
$api_key = '06WSSDM24HZUV01G';
// $api_url =
"h://api.thingspeak.com/channels/$channel_id/feeds.xml?re
sults=2&api_key=$api_key";
$api_url =
"h://api.thingspeak.com/channels/$channel_id/fields/$field_
id.$format?api_key=$api_key&minutes=1";
$xml= simplexml_load_file($api_url);
var_dump($xml->feeds->feed->field1);
$val = $xml->feeds->feed->field1;
$breathing_rate = (int)$val;
echo $breathing_rate;
if($breathing_rate < 12 and $breathing_rate > 30){
$keyword = 'low';
if ($breathing_rate > 30){
$keyword = 'high';
}
$msg = "Uh-ho your breathing rate is $breathing_rate.
This is too $keyword.";
$msg = wordwrap($msg, 70);
$mail->IsHTML(true);
$mail->AddAddress("xyz@gmail.com", "User");
$mail->SetFrom("brahamanyanupur@gmail.com",
"breatheBetter.com");
$mail->Subject = "breathing rate alert!";
$content = "<b>$msg</b>";
$mail->MsgHTML($content);
if(!$mail->Send()) {
echo "Error while sending Email.";
// var_dump($mail);
} else {
echo "Email sent successfully";
}
}
// sleep for 60 minutes
sleep(60);
}
?>