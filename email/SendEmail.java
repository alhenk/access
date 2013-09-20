// File Name SendEmail.java

import java.util.*;
import javax.mail.*;
import javax.mail.internet.*;
import javax.activation.*;

public class SendEmail
{
   public static void main(String [] args)
   {    
      // Recipient's email ID needs to be mentioned.
      String to = "Livinets.A@trei.lan";

      // Sender's email ID needs to be mentioned
      String from = "Koryagin.A@trei.lan";

      // Assuming you are sending email from localhost
      // String host = "127.0.0.1";
      String host = "192.168.32.100";
      // Get system properties
      Properties properties = System.getProperties();

      // Setup mail server
      properties.setProperty("mail.smtp.host", host);
      properties.setProperty("mail.user", "Koryagin.A");
      properties.setProperty("mail.password", "alhenalhen");
      properties.setProperty("mail.smtp.auth", "true");
      properties.setProperty("mail.smtp.port", "" + 587);
      properties.setProperty("mail.smtp.starttls.enable", "true");
      /*properties.put("mail.smtp.socketFactory.class",   
                "javax.net.SocketFactory");   
      properties.put("mail.smtp.socketFactory.fallback", "false"); */

      // Get the default Session object.
      // Session session = Session.getDefaultInstance(properties);
      SmtpAuthenticator authentication = new SmtpAuthenticator();
      Session session = Session.getDefaultInstance(properties, authentication);
    

      try{
         // Create a default MimeMessage object.
         //MimeMessage message = new MimeMessage(session);
         //javax.mail.Message message = new MimeMessage(session);
         MimeMessage message = new MimeMessage(session);


         // Set From: header field of the header.
         message.setFrom(new InternetAddress(from));

         // Set To: header field of the header.
         message.addRecipient(Message.RecipientType.TO,
                                  new InternetAddress(to));

         // Set Subject: header field
         // message.setSubject("This is the Subject Line!");
         message.setSubject("wtf");


         // Now set the actual message
         // message.setText("This is actual message");
        // message.setText("spam spam spm.... bougha gha gha ...:))))");



         // Create the message part 
         BodyPart messageBodyPart = new MimeBodyPart();

         // Fill the message
         messageBodyPart.setText("This is message body");
         
         // Create a multipar message
         Multipart multipart = new MimeMultipart();

         // Set text message part
         multipart.addBodyPart(messageBodyPart);

         // Part two is attachment
         messageBodyPart = new MimeBodyPart();
         String filename = "file.txt";
         DataSource source = new FileDataSource(filename);
         messageBodyPart.setDataHandler(new DataHandler(source));
         messageBodyPart.setFileName(filename);
         multipart.addBodyPart(messageBodyPart);

         // Send the complete message parts
         message.setContent(multipart );

         // Send message
         Transport.send(message);
         System.out.println("Sent message successfully....");
      }catch (MessagingException mex) {
         mex.printStackTrace();
      }
   }
}
