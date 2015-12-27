#ifndef LightSensor_h
#define LightSensor_h

class LightSensor {
	private:
		int _photoresistorPin = A0;
		
	public:
		int light;
		
		LightSensor(int);
		void update();
		JsonObject& createJsonObject(JsonObject&);
};

#endif