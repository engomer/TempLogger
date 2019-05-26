<?php
require("class.phpmailer.php");
$mail = new PHPMailer(); // create a new object
$mail->IsSMTP(); // enable SMTP
$mail->SMTPDebug = 1; // debugging: 1 = errors and messages, 2 = messages only
$mail->SMTPAuth = true; // authentication enabled
$mail->SMTPSecure = 'ssl'; // secure transfer enabled REQUIRED for GMail ssl or tls
$mail->Host = "MAIL SERVER NAME";
$mail->Port = 465; // or 587
$mail->IsHTML(true);
$mail->SetLanguage("tr", "phpmailer/language");
$mail->CharSet  ="utf-8";

$mail->Username = "MAIL ADDRESS"; // Mail address
$mail->Password = "PASSWORD"; // Password
$mail->SetFrom("MAIL ADDRESS", "SENDER NAME"); // Mail address


if(isset($_GET['DBCOLUMN1']) && isset($_GET['DBCOLUMN2'])){ 
$subject = $_GET['DBCOLUMN1'];
$body = $_GET['DBCOLUMN2'];
$mail->AddAddress("RECIPIENT ADDRESS"); // Recipient

$mail->Subject = $subject;
$mail->Body = "<br />BODY PART OF THE MAIL<br />$body";

if(!$mail->Send()){
                echo "Mailer Error: ".$mail->ErrorInfo;
} else {
                echo "Message has been sent";
}
}
?>
