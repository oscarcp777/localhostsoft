package fi.uba.drools.poker.rules;

import static org.junit.Assert.assertEquals;

import org.drools.KnowledgeBase;
import org.drools.logger.KnowledgeRuntimeLogger;
import org.drools.logger.KnowledgeRuntimeLoggerFactory;
import org.drools.runtime.StatefulKnowledgeSession;
import org.junit.Test;

import fi.uba.drools.poker.FactoryDRL;
import fi.uba.drools.poker.models.Action;
import fi.uba.drools.poker.models.Decision;
import fi.uba.drools.poker.models.Player;
import fi.uba.drools.poker.models.Table;

public class RulesTest {
	
	
	
	@Test
	public void testRegla1() {
		try {
			// Cargar las reglas
			KnowledgeBase kbase = FactoryDRL.readKnowledgeBase("pokerRules.drl");
			StatefulKnowledgeSession ksession = kbase.newStatefulKnowledgeSession();
			KnowledgeRuntimeLogger logger = KnowledgeRuntimeLoggerFactory.newConsoleLogger(ksession);

			Table t = new Table();
			t.setPotSize(Integer.valueOf(100));
			t.setMainPlayer(new Player("mainPlayer", 100));
			t.getMainPlayer().setRankHand(20);
			t.getMainPlayer().setPosition("BIGBLIND");
			t.setOpponentPlayer(new Player("opponentPlayer", 100));
			Decision opponentDecision = new Decision(Action.CALL,0);
			t.getOpponentPlayer().setDecision(opponentDecision);
			t.setBigBlind(Integer.valueOf(5));
			ksession.insert(t);
			ksession.fireAllRules();
			assertEquals(t.getMainPlayer().getDecision().getAction(),Action.RAISE);
			System.out.println("La accion del player es " + t.getMainPlayer().getDecision().getAction() + " a "+t.getMainPlayer().getDecision().getBetsize());
			logger.close();
		} catch (Throwable t) {
			t.printStackTrace();
		}
	}

}
