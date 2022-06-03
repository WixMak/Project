# package
import requests
import time
# send request while raspberry pi is on
while True:
  # send light check request
  requests.post('https://maker.ifttt.com/trigger/ambient_light_detect/json/with/key/{APIKEY}')
  # send distance check request
  requests.post('https://maker.ifttt.com/trigger/distance_check/json/with/key/{APIKEY}')
  # timeout
  time.sleep(0.01)
