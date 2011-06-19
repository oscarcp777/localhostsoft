package fi.uba.drools.poker.utils;

import java.util.Enumeration;
import java.util.ResourceBundle;

public class MapUtils {
	public static Integer getHandRange(String hand){
		ResourceBundle bundle= ResourceBundle.getBundle("properties.HandRange");
		Enumeration<String> keys= bundle.getKeys();
		while(keys.hasMoreElements()){
			String key=keys.nextElement();
			String value= bundle.getString(key);
			if(value.contains(hand)){
				return Integer.valueOf(key);
			}

		}
		return 0;
	}


}
