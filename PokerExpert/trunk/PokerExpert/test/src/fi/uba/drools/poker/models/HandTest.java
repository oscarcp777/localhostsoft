package fi.uba.drools.poker.models;

import java.util.ArrayList;
import java.util.Collection;

import junit.framework.Assert;

import org.junit.Test;

/**
 * Test suite for the Hand class.
 * 
 * @author Oscar Stigter
 */
public class HandTest {


	/**
	 * Tests the basics (good-weather).
	 */
	@Test
	public void testGetHandRange() {
		Hand hand =new Hand("As Qh");
		Assert.assertEquals(hand.getHandRange(), Integer.valueOf(5));
		hand =new Hand("As Js");
		Assert.assertEquals(hand.getHandRange(), Integer.valueOf(10));
		hand =new Hand("2s 2h");
		Assert.assertEquals(hand.getHandRange(), Integer.valueOf(20));
		hand =new Hand("9d Qc");
		Assert.assertEquals(hand.getHandRange(), Integer.valueOf(50));
		hand =new Hand("6c Qh");
		Assert.assertEquals(hand.getHandRange(), Integer.valueOf(60));
		hand =new Hand("8c Qc");
		Assert.assertEquals(hand.getHandRange(), Integer.valueOf(30));
		hand =new Hand("4h Ah");
		Assert.assertEquals(hand.getHandRange(), Integer.valueOf(20));
	}
	/**
	 * Tests the basics (good-weather).
	 */
	@Test
	public void testGetFormatRange() {

		Hand hand =new Hand("As Qh");
		System.out.println(hand.toString());
		System.out.println(hand.getFormatRange());
		Assert.assertEquals(hand.getFormatRange(), "AQo");
		hand =new Hand("As As");
		System.out.println(hand.getFormatRange());
		Assert.assertEquals(hand.getFormatRange(), "AA");
		hand =new Hand("2s 2h");
		System.out.println(hand.getFormatRange());
		Assert.assertEquals(hand.getFormatRange(), "22");
		hand =new Hand("9d Qc");
		System.out.println(hand.getFormatRange());
		Assert.assertEquals(hand.getFormatRange(), "Q9o");
		hand =new Hand("6c Qh");
		System.out.println(hand.getFormatRange());
		Assert.assertEquals(hand.getFormatRange(), "Q6o");
		hand =new Hand("8c Qc");
		System.out.println(hand.getFormatRange());
		Assert.assertEquals(hand.getFormatRange(), "Q8s");
		hand =new Hand("4h Ah");
		System.out.println(hand.getFormatRange());
		Assert.assertEquals(hand.getFormatRange(), "A4s");
	}

	/**
	 * Tests the basics (good-weather).
	 */
	@Test
	public void basics() {
		Hand hand = new Hand();
		Assert.assertNotNull(hand);
		Assert.assertEquals(0, hand.size());

		Card[] cards = hand.getCards();
		Assert.assertNotNull(cards);
		Assert.assertEquals(0, cards.length);

		hand.addCard(new Card("Th"));
		Assert.assertEquals(1, hand.size());
		cards = hand.getCards();
		Assert.assertNotNull(cards);
		Assert.assertEquals(1, cards.length);
		Assert.assertNotNull(cards[0]);
		Assert.assertEquals("Th", cards[0].toString());

		hand.addCards(new Card[]{new Card("2d")});
		Assert.assertEquals(2, hand.size());
		cards = hand.getCards();
		Assert.assertNotNull(cards);
		Assert.assertEquals(2, cards.length);
		Assert.assertEquals("2d", cards[1].toString());

		hand.removeAllCards();
		Assert.assertEquals(0, hand.size());
	}

	/**
	 * Tests the constructors (bad-weather).
	 */
	@Test
	public void constructors() {
		@SuppressWarnings("unused")
		Hand hand = null;

		// Null card array.
		try {
			Card[] cards = null;
			hand = new Hand(cards);
			Assert.fail("No exception thrown");
		} catch (IllegalArgumentException e) {
			// OK.
		}

		// Card array with a null card.
		try {
			Card[] cards = new Card[1];
			hand = new Hand(cards);
			Assert.fail("No exception thrown");
		} catch (IllegalArgumentException e) {
			// OK.
		}

		// Card array with too many cards.
		try {
			Card[] cards = new Card[11];
			hand = new Hand(cards);
			Assert.fail("No exception thrown");
		} catch (IllegalArgumentException e) {
			// OK.
		}

		// Null card collection.
		try {
			Collection<Card> cards = null;
			hand = new Hand(cards);
			Assert.fail("No exception thrown");
		} catch (IllegalArgumentException e) {
			// OK.
		}

		// Card collection with a null card.
		try {
			Collection<Card> cards = new ArrayList<Card>();
			cards.add(null);
			hand = new Hand(cards);
			Assert.fail("No exception thrown");
		} catch (IllegalArgumentException e) {
			// OK.
		}

		// Card array with too many cards.
		try {
			Card[] cards = new Card[11];
			hand = new Hand(cards);
			Assert.fail("No exception thrown");
		} catch (IllegalArgumentException e) {
			// OK.
		}
	}

}
