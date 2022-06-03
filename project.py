import requests
import time

while True:
  requests.post('https://maker.ifttt.com/trigger/ambient_light_detect/json/with/key/{APIKEY}')
  requests.post('https://maker.ifttt.com/trigger/distance_check/json/with/key/{APIKEY}')
  time.sleep(0.01)
