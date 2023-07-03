#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "GOKART_PBCOE"                         //change this
 
const char WIFI_SSID[] = "GOKARTPBCOE";               //change this
const char WIFI_PASSWORD[] = "GOKARTPBCOE";           //change this
const char AWS_IOT_ENDPOINT[] = "a37nlo9ieaaf6l-ats.iot.ap-south-1.amazonaws.com";       //change this
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAKq8sSkuMHR9PZVoxQOQtBuDuuJ2MA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMzAxMTkwOTIy
MjNaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDqIrj/y/oZOyzfdA1U
xIW54RCvXmZ0lXLINSDyvB+MChW4okvq0F2wsuJ/HDInV9+EsoXloBqdM2GkdD/z
vTs2eJ+/2bKVWDxNCD6bABBw+VFftgx+mjNcUztBIxxILfJRNQ3coWKc355lCk7D
47UZbl/nehFvPY0U36PTSKUrR+93F9GoYzw6IRW4NhwT6krbjBD6HeZC6Tu9FcE3
rkFUeqBSsWHjvFxwrv1/pjyA4L+aQ4tVAHSSwAX02OB+9vCQlfWbyZ4RZJtNd+KR
OctHaEQsMz/1262k5pz3piTgGQu1wc5dsyhc0ABUHZ7hlVMhSbpjYyfAouVGL8+K
MAc1AgMBAAGjYDBeMB8GA1UdIwQYMBaAFJoxOT+4ZR9TDuvbSO3ydySF2z/kMB0G
A1UdDgQWBBSyDCo5I028Z8D7IXy8kF43ihOMlDAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEANXuzmroYA1dazIynkUo3Q2ku
EdTQh2rRuUYcayUxEhrbXWWNlg9Hzw/3q4wHdlMM7/74Vmq6fCUlqoTScp8EoYE1
TDFhw50w4lfiYWXlAlAsHslXJ8dYyZL/N4Od9z6MtxMGBDvmMNGqV0EQwq8KwUf0
q4C5JJQJq8oB6YkPBoIZS5qtve5S2Y6m77VevsvWHFtzgXVFrl6y31uRuYX9iwrt
KTi8mR5yR01x4kOwa4Z9fpeBWYAc8aGju+FxNqnlB8gBwXeJkUzRAF7wwIAkbkO3
NyWbfGMalnnAC2MefCyxpheQHm/Z7Sk3O1WR1I4jxOg1v0+PloOPY3IGor5xUA==
-----END CERTIFICATE-----

 
 
)KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEA6iK4/8v6GTss33QNVMSFueEQr15mdJVyyDUg8rwfjAoVuKJL
6tBdsLLifxwyJ1ffhLKF5aAanTNhpHQ/8707Nnifv9mylVg8TQg+mwAQcPlRX7YM
fpozXFM7QSMcSC3yUTUN3KFinN+eZQpOw+O1GW5f53oRbz2NFN+j00ilK0fvdxfR
qGM8OiEVuDYcE+pK24wQ+h3mQuk7vRXBN65BVHqgUrFh47xccK79f6Y8gOC/mkOL
VQB0ksAF9NjgfvbwkJX1m8meEWSbTXfikTnLR2hELDM/9dutpOac96Yk4BkLtcHO
XbMoXNAAVB2e4ZVTIUm6Y2MnwKLlRi/PijAHNQIDAQABAoIBAQDo72ygSJ3kVkQZ
d4r/x5jHSgvgfQlveXO9jWXfOJwmJa5gh08CKRTdA8tk7HdVPw5IJZgi0HtJ5GGD
TIiHhL8RPUaphvstq6Aqf0ZRzOmOi+ySTTr3BZCNjNzJvBWaFeQbOK42z3SdX7hl
C7E7ICL/Txko4P/RbSocFzcUsBRrDfm97VNYhahC8YPIaxlpio3WTCnaSmjHTqzT
q+hcmDbcCYvZYKxyROflIyK0ujSuiqraNgPF/GWNlfF+IC4ayShrCHnOBZj42hKd
zmP+79AdBVLSToG6809ZctoJNsshUWSo7m0N9WetI6usrO6PpvpZJuahGQvezclu
l/oJiNxhAoGBAP7Qd1KMp1cOc9IH9qocFD8uWc32+bJx0q6HqodwlM4NmsrjdCTI
QhH/pmWjhgKx788ph0y4M4koY90/aa8nc3p5jfM0UgSuUTTk8Pt5GYaYTl0DLPE7
ykbk4KOrS3l1qGmZBPioZe8WyUjLfQchNupRtohv4/ibkWBbVAFKNrfNAoGBAOs5
n8noxTOQqaM3UlHWJf7rpv2c3xxVpI7nSkCYhOt046SIUoooXMyvbTWuyfyMBwbz
UEBPBPc30oeHclc7IQ4cxqID1dGwTWnbKOdJDHq9AKhIHKjwqc3iOYdHFPDTKCRF
vWd3qBiNqh2KxMnhYhKaoqtrc3rcTKMK5lNirtUJAoGAH+HljCadKX9dboIgkthA
kEc0ZVjplTI4si23YIrtk3qQS6J5/cAwxB/AqibztZKd9sWzcB38FMVA+YXdq1S8
Vi6vXCbHvF4zOvMKU+yrDPQxmeGz1dstTAGHOfNM1j2qfMvwm0w2tNudA8ayNhop
zNe8hwW4+Ho+jlffAupOPmECgYEAnPhJT14MKwsAiTCjuITluiXbvCZxJOFp/QsP
m+er28yXFPb7zcJ9mwH+KPLJS8TN869vAFs6/xa7YUHb5aZJurctPnS8vT+fiWJ8
+0reDxINXD8zEPH4/rFWnpWqvcLLaNk5OdC51hjDSw+NnwLOhYe3whjkaTqV0b+2
UDLsZLECgYEAlo1nncfdhRiydBgRHsbzOxqnFV6t9IwH0M8rUbIZWZiOP8Sy97rD
CSz+BC4rhjBkvp0qmz9E1uDKtV5VN9CdrFJ5gzdIYoyfWBqVB29buM8ng5ZWcfLz
G2ZYcutkuXmzCx0hPDJz50QMq4Z7a9fp3dkz//SSc7yzenSuRfrkL7Y=
-----END RSA PRIVATE KEY-----

 
)KEY";