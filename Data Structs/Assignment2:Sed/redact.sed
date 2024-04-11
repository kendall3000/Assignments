#!/bin/sed -f

# Redact Driver’s License numbers
s/[A-Z]{2}(DL )?[0-9]{6,8}/DL <redacted>/g

# Redact Credit Card Numbers
s/4[0-9]{3}(-?[0-9]{4}){3}/VISA-\1/g
s/5[0-9]{3}(-?[0-9]{4}){3}/MC-\1/g
s/3[47][0-9]{2}(-?[0-9]{4}){2}/AMEX-\1/g
s/6[0-9]{3}(-?[0-9]{4}){3}/DISC-\1/g

# Redact Texas Vehicle License Plate numbers
s/(TX ?)?[0-9A-Z]{3,4}(-?[0-9A-Z]{3,4})?/<redacted>/g

# Update current date placeholder
s/<date>/$(date +%m\/%d\/%Y)/g

# Replace <mname> with the full municipality name
s/<mname>/City of Brook Haven, Connecticut/g

