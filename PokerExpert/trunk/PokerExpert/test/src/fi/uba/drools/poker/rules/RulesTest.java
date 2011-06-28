package fi.uba.drools.poker.rules;

import static org.junit.Assert.assertEquals;

import java.util.HashMap;

import org.drools.KnowledgeBase;
import org.drools.runtime.StatefulKnowledgeSession;
import org.junit.Test;

import fi.uba.drools.poker.FactoryDRL;
import fi.uba.drools.poker.models.Action;
import fi.uba.drools.poker.models.Decision;
import fi.uba.drools.poker.models.Hand;
import fi.uba.drools.poker.models.Player;
import fi.uba.drools.poker.models.Table;
import fi.uba.drools.poker.utils.Constants;

@SuppressWarnings("restriction")
public class RulesTest {
	
	public static String POSITION_PLAYER="BIGBLIND";
	private StatefulKnowledgeSession getSession(){
		KnowledgeBase kbase = FactoryDRL.readKnowledgeBase("pokerRules.drl");
		StatefulKnowledgeSession ksession = kbase.newStatefulKnowledgeSession();
		return ksession;
	}
	
	private Table createTable(HashMap<String, Object> mapaAtributos){
		Table table = new Table();

//		ATRIBUTOS DEL jugador
		Player mainPlayer=new Player("mainPlayer", (Integer) mapaAtributos.get(Constants.Atributos.MAIN_PLAYER_CASH));
		mainPlayer.setPosition((String) mapaAtributos.get(Constants.Atributos.POSITION_MAIN_PLAYER));
		mainPlayer.setHand((Hand) mapaAtributos.get(Constants.Atributos.HAND_MAIN_PLAYER));
		mainPlayer.setDecision(new Decision(Action.CONTINUE,0));
		mainPlayer.setBet((Integer) mapaAtributos.get(Constants.Atributos.BET_MAIN_PLAYER));
//		cargo atributos del oponente
		Player opponentPlayer=new Player("opponentPlayer", (Integer) mapaAtributos.get(Constants.Atributos.OPPONENT_PLAYER_CASH));
		
		opponentPlayer.setDecision(new Decision((Action) mapaAtributos.get(Constants.Atributos.DECISION_ACTION_OPPONENT),0));
		opponentPlayer.setStrategy((String) mapaAtributos.get(Constants.Atributos.STRATEGY_OPPONENT_PLAYER));
		opponentPlayer.setBet((Integer) mapaAtributos.get(Constants.Atributos.BET_OPPONENT_PLAYER));
		//		cargo campos de la mesa
		table.setMainPlayer(mainPlayer);
		table.setOpponentPlayer(opponentPlayer);
		table.setPotSize((Integer) mapaAtributos.get(Constants.Atributos.POTSIZE));
		table.setBigBlind((Integer) mapaAtributos.get(Constants.Atributos.BIG_BLIND));
		return table;
	}
	/**
	 * rule "Soy luz grande, oponente hizo call y mi mano esta en el TOP 30%"
	 */
	@Test
	public void testRule1() {
		try {
			StatefulKnowledgeSession session = getSession();
			HashMap<String, Object> mapaAtributos=new HashMap<String, Object>();
			mapaAtributos.put(Constants.Atributos.BET_MAIN_PLAYER, 10);
			mapaAtributos.put(Constants.Atributos.BET_OPPONENT_PLAYER, 10);
			mapaAtributos.put(Constants.Atributos.BIG_BLIND, 5);
			mapaAtributos.put(Constants.Atributos.DECISION_ACTION_OPPONENT, Action.CALL);
			mapaAtributos.put(Constants.Atributos.HAND_MAIN_PLAYER, new Hand("Kd Js"));
			mapaAtributos.put(Constants.Atributos.MAIN_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.OPPONENT_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.POSITION_MAIN_PLAYER, Constants.Blind.BIG_BLIND);
			mapaAtributos.put(Constants.Atributos.POTSIZE, 20);
			mapaAtributos.put(Constants.Atributos.STRATEGY_OPPONENT_PLAYER, Constants.Strategy.AGGRESIVE);
			
			Table t=createTable(mapaAtributos);
			session.insert(t);
			session.fireAllRules();
			System.out.println("TEST RULE 1: La accion del player es " + t.getMainPlayer().getDecision().getAction() + " a "+t.getMainPlayer().getDecision().getBetsize());
			assertEquals(t.getMainPlayer().getDecision().getAction(),Action.RAISE);			
		} catch (Throwable t) {
			t.printStackTrace();
		}
	}
	
	/**
	 * rule "Soy luz grande, oponente hizo call y mi mano esta entre TOP 30% - 40%"
	 */
	@Test
	public void testRule2() {
		try {
			StatefulKnowledgeSession session = getSession();
			HashMap<String, Object> mapaAtributos=new HashMap<String, Object>();
			mapaAtributos.put(Constants.Atributos.BET_MAIN_PLAYER, 10);
			mapaAtributos.put(Constants.Atributos.BET_OPPONENT_PLAYER, 10);
			mapaAtributos.put(Constants.Atributos.BIG_BLIND, 5);
			mapaAtributos.put(Constants.Atributos.DECISION_ACTION_OPPONENT, Action.CALL);
			mapaAtributos.put(Constants.Atributos.HAND_MAIN_PLAYER, new Hand("Ks 8d"));
			mapaAtributos.put(Constants.Atributos.MAIN_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.OPPONENT_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.POSITION_MAIN_PLAYER, Constants.Blind.BIG_BLIND);
			mapaAtributos.put(Constants.Atributos.POTSIZE, 20);
			mapaAtributos.put(Constants.Atributos.STRATEGY_OPPONENT_PLAYER, Constants.Strategy.TIGHT);
			
			Table t=createTable(mapaAtributos);
			session.insert(t);
			session.fireAllRules();
			System.out.println("TEST RULE 2:La accion del player es " + t.getMainPlayer().getDecision().getAction() + " a "+t.getMainPlayer().getDecision().getBetsize());
			assertEquals(t.getMainPlayer().getDecision().getAction(),Action.RAISE);			
		} catch (Throwable t) {
			t.printStackTrace();
		}
	}

	
	/**
	 * rule "Soy luz grande, oponente hizo call y mi mano esta en el TOP 50%"
	 */
	@Test
	public void testRule3() {
		try {
			StatefulKnowledgeSession session = getSession();
			HashMap<String, Object> mapaAtributos=new HashMap<String, Object>();
			mapaAtributos.put(Constants.Atributos.BET_MAIN_PLAYER, 10);
			mapaAtributos.put(Constants.Atributos.BET_OPPONENT_PLAYER, 10);
			mapaAtributos.put(Constants.Atributos.BIG_BLIND, 5);
			mapaAtributos.put(Constants.Atributos.DECISION_ACTION_OPPONENT, Action.CALL);
			mapaAtributos.put(Constants.Atributos.HAND_MAIN_PLAYER, new Hand("8s 7d"));
			mapaAtributos.put(Constants.Atributos.MAIN_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.OPPONENT_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.POSITION_MAIN_PLAYER, Constants.Blind.BIG_BLIND);
			mapaAtributos.put(Constants.Atributos.POTSIZE, 20);
			mapaAtributos.put(Constants.Atributos.STRATEGY_OPPONENT_PLAYER, Constants.Strategy.TIGHT);
			
			Table t=createTable(mapaAtributos);
			session.insert(t);
			session.fireAllRules();
			System.out.println("TEST RULE 3:La accion del player es " + t.getMainPlayer().getDecision().getAction() + " a "+t.getMainPlayer().getDecision().getBetsize());
			assertEquals(t.getMainPlayer().getDecision().getAction(),Action.RAISE);			
		} catch (Throwable t) {
			t.printStackTrace();
		}
	}
	
	
	/**
	 * rule "Soy luz grande, oponente hizo call y mi mano esta entre TOP >50% - 100%"
	 */
	@Test
	public void testRule4() {
		try {
			StatefulKnowledgeSession session = getSession();
			HashMap<String, Object> mapaAtributos=new HashMap<String, Object>();
			mapaAtributos.put(Constants.Atributos.BET_MAIN_PLAYER, 10);
			mapaAtributos.put(Constants.Atributos.BET_OPPONENT_PLAYER, 10);
			mapaAtributos.put(Constants.Atributos.BIG_BLIND, 5);
			mapaAtributos.put(Constants.Atributos.DECISION_ACTION_OPPONENT, Action.CALL);
			mapaAtributos.put(Constants.Atributos.HAND_MAIN_PLAYER, new Hand("7s 3d"));
			mapaAtributos.put(Constants.Atributos.MAIN_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.OPPONENT_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.POSITION_MAIN_PLAYER, Constants.Blind.BIG_BLIND);
			mapaAtributos.put(Constants.Atributos.POTSIZE, 20);
			mapaAtributos.put(Constants.Atributos.STRATEGY_OPPONENT_PLAYER, Constants.Strategy.TIGHT);
			
			Table t=createTable(mapaAtributos);
			session.insert(t);
			session.fireAllRules();
			System.out.println("TEST RULE 4:La accion del player es " + t.getMainPlayer().getDecision().getAction());
			assertEquals(t.getMainPlayer().getDecision().getAction(),Action.CHECK);			
		} catch (Throwable t) {
			t.printStackTrace();
		}
	}
	
	
	/**
	 * rule "Soy luz grande, oponente hizo raise y mi mano esta entre TOP 5% - 20%"
	 */
	@Test
	public void testRule5() {
		try {
			StatefulKnowledgeSession session = getSession();
			HashMap<String, Object> mapaAtributos=new HashMap<String, Object>();
			mapaAtributos.put(Constants.Atributos.BET_MAIN_PLAYER, 10);
			mapaAtributos.put(Constants.Atributos.BET_OPPONENT_PLAYER, 35);
			mapaAtributos.put(Constants.Atributos.BIG_BLIND, 5);
			mapaAtributos.put(Constants.Atributos.DECISION_ACTION_OPPONENT, Action.RAISE);
			mapaAtributos.put(Constants.Atributos.HAND_MAIN_PLAYER, new Hand("As 9d"));
			mapaAtributos.put(Constants.Atributos.MAIN_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.OPPONENT_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.POSITION_MAIN_PLAYER, Constants.Blind.BIG_BLIND);
			mapaAtributos.put(Constants.Atributos.POTSIZE, 45);
			mapaAtributos.put(Constants.Atributos.STRATEGY_OPPONENT_PLAYER, Constants.Strategy.TIGHT);
			
			Table t=createTable(mapaAtributos);
			session.insert(t);
			session.fireAllRules();
			System.out.println("TEST RULE 5:La accion del player es " + t.getMainPlayer().getDecision().getAction() + " a "+t.getMainPlayer().getDecision().getBetsize());
			assertEquals(t.getMainPlayer().getDecision().getAction(),Action.RAISE);
		} catch (Throwable t) {
			t.printStackTrace();
		}
	}
	
	/**
	 * rule "Soy luz grande, oponente hizo raise y mi mano esta entre TOP 30%"
	 */
	@Test
	public void testRule6() {
		try {
			StatefulKnowledgeSession session = getSession();
			HashMap<String, Object> mapaAtributos=new HashMap<String, Object>();
			mapaAtributos.put(Constants.Atributos.BET_MAIN_PLAYER, 10);
			mapaAtributos.put(Constants.Atributos.BET_OPPONENT_PLAYER, 35);
			mapaAtributos.put(Constants.Atributos.BIG_BLIND, 5);
			mapaAtributos.put(Constants.Atributos.DECISION_ACTION_OPPONENT, Action.RAISE);
			mapaAtributos.put(Constants.Atributos.HAND_MAIN_PLAYER, new Hand("Kd 8d"));
			mapaAtributos.put(Constants.Atributos.MAIN_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.OPPONENT_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.POSITION_MAIN_PLAYER, Constants.Blind.BIG_BLIND);
			mapaAtributos.put(Constants.Atributos.POTSIZE, 45);
			mapaAtributos.put(Constants.Atributos.STRATEGY_OPPONENT_PLAYER, Constants.Strategy.AGGRESIVE);
			
			Table t=createTable(mapaAtributos);
			session.insert(t);
			session.fireAllRules();
			System.out.println("TEST RULE 6:La accion del player es " + t.getMainPlayer().getDecision().getAction() + " a "+t.getMainPlayer().getDecision().getBetsize());
			assertEquals(t.getMainPlayer().getDecision().getAction(),Action.RAISE);		
		} catch (Throwable t) {
			t.printStackTrace();
		}
	}
	
	
	/**
	 * rule "Soy luz grande, oponente hizo raise y mi mano esta entre TOP 40% - 60%"
	 */
	@Test
	public void testRule7() {
		try {
			StatefulKnowledgeSession session = getSession();
			HashMap<String, Object> mapaAtributos=new HashMap<String, Object>();
			mapaAtributos.put(Constants.Atributos.BET_MAIN_PLAYER, 10);
			mapaAtributos.put(Constants.Atributos.BET_OPPONENT_PLAYER, 100);
			mapaAtributos.put(Constants.Atributos.BIG_BLIND, 10);
			mapaAtributos.put(Constants.Atributos.DECISION_ACTION_OPPONENT, Action.RAISE);
			mapaAtributos.put(Constants.Atributos.HAND_MAIN_PLAYER, new Hand("7d 5d"));
			mapaAtributos.put(Constants.Atributos.MAIN_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.OPPONENT_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.POSITION_MAIN_PLAYER, Constants.Blind.BIG_BLIND);
			mapaAtributos.put(Constants.Atributos.POTSIZE, 45);
			mapaAtributos.put(Constants.Atributos.STRATEGY_OPPONENT_PLAYER, Constants.Strategy.AGGRESIVE);
			
			Table t=createTable(mapaAtributos);
			session.insert(t);
			session.fireAllRules();
			System.out.println("TEST RULE 7:La accion del player es " + t.getMainPlayer().getDecision().getAction() + " a "+t.getMainPlayer().getDecision().getBetsize());
			assertEquals(t.getMainPlayer().getDecision().getAction(),Action.FOLD);			
		} catch (Throwable t) {
			t.printStackTrace();
		}
	}
	
	
	/**
	 * rule "Soy luz grande, oponente hizo raise y mi mano esta entre TOP 70% - 80%"
	 */
	@Test
	public void testRule8() {
		try {
			StatefulKnowledgeSession session = getSession();
			HashMap<String, Object> mapaAtributos=new HashMap<String, Object>();
			mapaAtributos.put(Constants.Atributos.BET_MAIN_PLAYER, 10);
			mapaAtributos.put(Constants.Atributos.BET_OPPONENT_PLAYER, 20);
			mapaAtributos.put(Constants.Atributos.BIG_BLIND, 10);
			mapaAtributos.put(Constants.Atributos.DECISION_ACTION_OPPONENT, Action.RAISE);
			mapaAtributos.put(Constants.Atributos.HAND_MAIN_PLAYER, new Hand("Qc 5d"));
			mapaAtributos.put(Constants.Atributos.MAIN_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.OPPONENT_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.POSITION_MAIN_PLAYER, Constants.Blind.BIG_BLIND);
			mapaAtributos.put(Constants.Atributos.POTSIZE, 45);
			mapaAtributos.put(Constants.Atributos.STRATEGY_OPPONENT_PLAYER, Constants.Strategy.AGGRESIVE);
			
			Table t=createTable(mapaAtributos);
			session.insert(t);
			session.fireAllRules();
			System.out.println("TEST RULE 8:La accion del player es " + t.getMainPlayer().getDecision().getAction() + " a "+t.getMainPlayer().getDecision().getBetsize());
			assertEquals(t.getMainPlayer().getDecision().getAction(),Action.FOLD);			
		} catch (Throwable t) {
			t.printStackTrace();
		}
	}
	
	
	/**
	 * rule "Soy luz grande, oponente hizo raise y mi mano esta entre TOP 90% - 100%"
	 */
	@Test
	public void testRule9() {
		try {
			StatefulKnowledgeSession session = getSession();
			HashMap<String, Object> mapaAtributos=new HashMap<String, Object>();
			mapaAtributos.put(Constants.Atributos.BET_MAIN_PLAYER, 10);
			mapaAtributos.put(Constants.Atributos.BET_OPPONENT_PLAYER, 20);
			mapaAtributos.put(Constants.Atributos.BIG_BLIND, 10);
			mapaAtributos.put(Constants.Atributos.DECISION_ACTION_OPPONENT, Action.RAISE);
			mapaAtributos.put(Constants.Atributos.HAND_MAIN_PLAYER, new Hand("6c 3d"));
			mapaAtributos.put(Constants.Atributos.MAIN_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.OPPONENT_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.POSITION_MAIN_PLAYER, Constants.Blind.BIG_BLIND);
			mapaAtributos.put(Constants.Atributos.POTSIZE, 45);
			mapaAtributos.put(Constants.Atributos.STRATEGY_OPPONENT_PLAYER, Constants.Strategy.AGGRESIVE);
			
			Table t=createTable(mapaAtributos);
			session.insert(t);
			session.fireAllRules();
			System.out.println("TEST RULE 9:La accion del player es " + t.getMainPlayer().getDecision().getAction() + " a "+t.getMainPlayer().getDecision().getBetsize());
			assertEquals(t.getMainPlayer().getDecision().getAction(),Action.FOLD);			
		} catch (Throwable t) {
			t.printStackTrace();
		}
	}
	
	/**
	 * rule "Soy boton y mi mano esta en el TOP 50%"
	 */
	@Test
	public void testRule10() {
		try {
			StatefulKnowledgeSession session = getSession();
			HashMap<String, Object> mapaAtributos=new HashMap<String, Object>();
			mapaAtributos.put(Constants.Atributos.BET_MAIN_PLAYER, 10);
			mapaAtributos.put(Constants.Atributos.BET_OPPONENT_PLAYER, 20);
			mapaAtributos.put(Constants.Atributos.BIG_BLIND, 10);
			mapaAtributos.put(Constants.Atributos.DECISION_ACTION_OPPONENT, Action.CONTINUE);
			mapaAtributos.put(Constants.Atributos.HAND_MAIN_PLAYER, new Hand("Ac Kd"));
			mapaAtributos.put(Constants.Atributos.MAIN_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.OPPONENT_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.POSITION_MAIN_PLAYER, Constants.Blind.SMALL_BLIND);
			mapaAtributos.put(Constants.Atributos.POTSIZE, 45);
			mapaAtributos.put(Constants.Atributos.STRATEGY_OPPONENT_PLAYER, Constants.Strategy.TIGHT);
			
			Table t=createTable(mapaAtributos);
			session.insert(t);
			session.fireAllRules();
			System.out.println("TEST RULE 10:La accion del player es " + t.getMainPlayer().getDecision().getAction() + " a "+t.getMainPlayer().getDecision().getBetsize());
			assertEquals(t.getMainPlayer().getDecision().getAction(),Action.RAISE);			
		} catch (Throwable t) {
			t.printStackTrace();
		}
	}
	
	/**
	 * rule "Soy boton y mi mano esta en el TOP 60% - 80%"
	 */
	@Test
	public void testRule11() {
		try {
			StatefulKnowledgeSession session = getSession();
			HashMap<String, Object> mapaAtributos=new HashMap<String, Object>();
			mapaAtributos.put(Constants.Atributos.BET_MAIN_PLAYER, 10);
			mapaAtributos.put(Constants.Atributos.BET_OPPONENT_PLAYER, 20);
			mapaAtributos.put(Constants.Atributos.BIG_BLIND, 10);
			mapaAtributos.put(Constants.Atributos.DECISION_ACTION_OPPONENT, Action.CONTINUE);
			mapaAtributos.put(Constants.Atributos.HAND_MAIN_PLAYER, new Hand("Qc 5d"));
			mapaAtributos.put(Constants.Atributos.MAIN_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.OPPONENT_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.POSITION_MAIN_PLAYER, Constants.Blind.SMALL_BLIND);
			mapaAtributos.put(Constants.Atributos.POTSIZE, 45);
			mapaAtributos.put(Constants.Atributos.STRATEGY_OPPONENT_PLAYER, Constants.Strategy.TIGHT);
			
			Table t=createTable(mapaAtributos);
			session.insert(t);
			session.fireAllRules();
			System.out.println("TEST RULE 11:La accion del player es " + t.getMainPlayer().getDecision().getAction() + " a "+t.getMainPlayer().getDecision().getBetsize());
			assertEquals(t.getMainPlayer().getDecision().getAction(),Action.RAISE);			
		} catch (Throwable t) {
			t.printStackTrace();
		}
	}
	/**
	 * rule "Soy boton y mi mano esta entre TOP 90% - 100%"
	 */
	@Test
	public void testRule12() {
		try {
			StatefulKnowledgeSession session = getSession();
			HashMap<String, Object> mapaAtributos=new HashMap<String, Object>();
			mapaAtributos.put(Constants.Atributos.BET_MAIN_PLAYER, 10);
			mapaAtributos.put(Constants.Atributos.BET_OPPONENT_PLAYER, 20);
			mapaAtributos.put(Constants.Atributos.BIG_BLIND, 10);
			mapaAtributos.put(Constants.Atributos.DECISION_ACTION_OPPONENT, Action.CONTINUE);
			mapaAtributos.put(Constants.Atributos.HAND_MAIN_PLAYER, new Hand("6c 3d"));
			mapaAtributos.put(Constants.Atributos.MAIN_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.OPPONENT_PLAYER_CASH, 100);
			mapaAtributos.put(Constants.Atributos.POSITION_MAIN_PLAYER, Constants.Blind.SMALL_BLIND);
			mapaAtributos.put(Constants.Atributos.POTSIZE, 45);
			mapaAtributos.put(Constants.Atributos.STRATEGY_OPPONENT_PLAYER, Constants.Strategy.TIGHT);
			
			Table t=createTable(mapaAtributos);
			session.insert(t);
			session.fireAllRules();
			System.out.println("TEST RULE 12:La accion del player es " + t.getMainPlayer().getDecision().getAction() + " a "+t.getMainPlayer().getDecision().getBetsize());
			assertEquals(t.getMainPlayer().getDecision().getAction(),Action.FOLD);			
		} catch (Throwable t) {
			t.printStackTrace();
		}
	}
}
