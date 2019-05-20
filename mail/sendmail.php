<?php
require("class.phpmailer.php");
$mail = new PHPMailer(); // create a new object
$mail->IsSMTP(); // enable SMTP
$mail->SMTPDebug = 1; // debugging: 1 = errors and messages, 2 = messages only
$mail->SMTPAuth = true; // authentication enabled
$mail->SMTPSecure = 'ssl'; // secure transfer enabled REQUIRED for GMail
$mail->Host = "smtp.gmail.com";
$mail->Port = 465; // or 587
$mail->IsHTML(true);
$mail->SetLanguage("tr", "phpmailer/language");
$mail->CharSet  ="utf-8";

$mail->Username = "omergsensor@gmail.com"; // Mail adresi
$mail->Password = "hdxomaxafdyljaki"; // Parola
$mail->SetFrom("omergsensor@gmail.com", "ÖmerG"); // Mail adresi

if(isset($_GET['mailto']) && isset($_GET['subject']) && isset($_GET['body'])){ 
$mailto = $_GET['mailto'];
$subject = $_GET['subject'];
$body = $_GET['body'];
$mail->AddAddress($mailto); // Gönderilecek kişi

$mail->Subject = $subject;
$mail->Body = "$name<br />$email<br />$subject<br />$body";

if(!$mail->Send()){
                echo "Mailer Error: ".$mail->ErrorInfo;
} else {
                echo "Message has been sent";
}
}
?>