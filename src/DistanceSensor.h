#ifndef DistanceSensor_h
#define DistanceSensor_h

class DistanceSensor {
	private:
		uint8_t _echoPin;
		uint8_t _trigPin;
		unsigned long microsecondsToInches();
		unsigned long microsecondsToCentimeters();
		
	public:
		unsigned long inches;
		unsigned long centimeters;
		unsigned long microseconds;
		
		DistanceSensor(uint8_t, uint8_t);
		~DistanceSensor();
		void update();
		JsonObject& createJsonObject(JsonObject&);
};

#endif