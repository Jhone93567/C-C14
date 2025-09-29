sudo apt-get install mailutils
echo "Sending e-mail after pipeline completion" | mail -s "Pipeline report" ${EMAIL_DESTINATARIO}
