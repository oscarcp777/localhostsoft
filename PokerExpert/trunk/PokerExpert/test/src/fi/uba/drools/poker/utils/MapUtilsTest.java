package fi.uba.drools.poker.utils;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class MapUtilsTest {

	@Test
	public void testGetMapHandRange(){
		assertEquals(MapUtils.getHandRange("82o"),Integer.valueOf(100));
		assertEquals(MapUtils.getHandRange("JTs"),Integer.valueOf(10));
		assertEquals(MapUtils.getHandRange("K7s"),Integer.valueOf(40));
		assertEquals(MapUtils.getHandRange("J5s"),Integer.valueOf(60));
		assertEquals(MapUtils.getHandRange("95o"),Integer.valueOf(90));
	}
	
}
