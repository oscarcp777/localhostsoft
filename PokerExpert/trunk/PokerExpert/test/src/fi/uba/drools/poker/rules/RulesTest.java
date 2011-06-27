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
			mapaAtributos.put(Constants.Atributos.POTSIZE, 100);
			mapaAtributos.put(Constants.Atributos.STRATEGY_OPPONENT_PLAYER, Constants.Strategy.AGGRESIVE);
			
			Table t=createTable(mapaAtributos);
			session.insert(t);
			session.fireAllRules();
			assertEquals(t.getMainPlayer().getDecision().getAction(),Action.RAISE);
			System.out.println("La accion del player es " + t.getMainPlayer().getDecision().getAction() + " a "+t.getMainPlayer().getDecision().getBetsize());
		} catch (Throwable t) {
			t.printStackTrace();
		}
	}

}
