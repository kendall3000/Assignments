#!/usr/bin/env python3
import math

def haversine(lat1, long1, lat2, long2):
	
	radiusOfEarthInMiles = 3958.8
	
	lat1Radians = math.radians(lat1)
	long1Radians = math.radians(long1)
	lat2Radians = math.radians(lat2)
	long2Radians = math.radians(long2)
	
	a = pow(math.sin((lat2Radians-lat1Radians)/2), 2) + math.cos(lat1Radians)*math.cos(lat2Radians)*pow(math.sin((long2Radians-long1Radians)/2), 2)
	c = 2*math.atan2(math.sqrt(a), math.sqrt(1-a))
	
	return radiusOfEarthInMiles*c
	
	
lat1 = 29.5827351
long1 = -98.621094

lat2 = 29.4259671
long2 = -98.4883306

dist = haversine(lat1,long1,lat2,long2)

print("The distance between UTSA Main campus: ("+str(lat1)+","+str(long1)+") and the Alamo: ("+str(lat2)+","+str(long2)+") is " + str(dist) + " miles.")