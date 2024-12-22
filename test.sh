# Set debug value to true or false to (de)activate output

debug=true

# Declare constants

ClientID="d9ghxx9tc838h8vmykh3"
ClientSecret="561b9b30349b4291b9a37fb496969323"
BaseUrl="https://openapi.tuyaeu.com"
EmptyBodyEncoded="e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
tuyatime=`(date +%s)`
tuyatime=$tuyatime"000"
if ($debug) then echo Tuyatime is now $tuyatime; fi;


# Get Access Token

URL="/v1.0/token?grant_type=1"

StringToSign="${ClientID}${tuyatime}GET\n${EmptyBodyEncoded}\n\n${URL}"
if ($debug) then echo StringToSign is now $StringToSign; fi;

AccessTokenSign=$(printf $StringToSign | openssl sha256 -hmac  "$ClientSecret" | tr '[:lower:]' '[:upper:]' |sed "s/.* //g")
if ($debug) then echo AccessTokenSign is now $AccessTokenSign; fi;

AccessTokenResponse=$(curl -sSLkX GET "$BaseUrl$URL" -H "sign_method: HMAC-SHA256" -H "client_id: $ClientID" -H "t: $tuyatime"  -H "mode: cors" -H "Content-Type: application/json" -H "sign: $AccessTokenSign")
if ($debug) then echo AccessTokenResponse is now $AccessTokenResponse; fi;

AccessToken=$(echo $AccessTokenResponse | sed "s/.*\"access_token\":\"//g"  |sed "s/\".*//g")
if ($debug) then echo Access token is now $AccessToken; fi;

# Send Device status request

URL="/v1.0/iot-03/devices/status?device_ids=bfaef501e3f539ca8fvmou"

StringToSign="${ClientID}${AccessToken}${tuyatime}GET\n${EmptyBodyEncoded}\n\n${URL}"
if ($debug) then echo StringToSign is now $StringToSign; fi;

RequestSign=$(printf $StringToSign | openssl sha256 -hmac  "$ClientSecret" | tr '[:lower:]' '[:upper:]' |sed "s/.* //g")
if ($debug) then echo RequestSign is now $RequestSign; fi;

RequestResponse=$(curl -sSLkX GET "$BaseUrl$URL" -H "sign_method: HMAC-SHA256" -H "client_id: $ClientID" -H "t: $tuyatime"  -H "mode: cors" -H "Content-Type: application/json" -H "sign: $RequestSign" -H "access_token: $AccessToken")
if ($debug) then echo RequestResponse is now $RequestResponse; fi;
