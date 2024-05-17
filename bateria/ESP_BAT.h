//El procedimiento para medir el voltaje de la batería se puede consultar en: https://github.com/Xinyuan-LilyGO/TTGO-T-Display/issues/35
 class ESP_BAT
{
  private:
  #define PWR_EN 14
  #define BAT_ADC 34
  #define BAT_REF 32
  float ADC_val;
  float V_bat;
  int V_percent;
  
  
  public:
  
  float get_voltage()
  { 
     ADC_val=analogRead(BAT_ADC);
     V_bat=(ADC_val/4095)*2*3.3*1.1; //2 y 3.3 están dados por las características del divisor de voltaje usado para leer el V_bat.
     digitalWrite(PWR_EN,LOW);
     return V_bat;
                                     
  }

  boolean isCharging(){
     boolean charging;
     ADC_val=analogRead(BAT_ADC);
     V_bat=(ADC_val/4095)*2*3.3*1.1;
     digitalWrite(PWR_EN,LOW);
     if(V_bat>4.5)charging=true;
     else charging=false;
     return charging;
  }
 
};
