package fi.uba.drools.poker.controller;

import org.drools.KnowledgeBase;
import org.drools.runtime.StatefulKnowledgeSession;

import fi.uba.drools.poker.FactoryDRL;
import fi.uba.drools.poker.models.Action;
import fi.uba.drools.poker.models.Card;
import fi.uba.drools.poker.models.Decision;
import fi.uba.drools.poker.models.Hand;
import fi.uba.drools.poker.models.Player;
import fi.uba.drools.poker.models.Table;
import fi.uba.drools.poker.view.Aumento;
import fi.uba.drools.poker.view.Principal;
import fi.uba.drools.poker.view.Recomendacion;

/**
 * Controlador principal de la aplicación y punto de entrada de la misma
 * @author Santiago
 *
 */
public class MainController {
	
	private Principal principalView;
	private Recomendacion recomendationView;
	private Aumento aumentoView;
	private Table table;
	
	public MainController(){
		initialize();
	}
	
	public void runApp(){
		java.awt.EventQueue.invokeLater(new Runnable() {

            public void run() {
                principalView.setVisible(true);
            }
        });

	}
	
	
	private void initialize(){
		principalView = new Principal();
		principalView.addRecomendationListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
            	getDecision();
            }
        });
		
	}
	
	private void getDecision(){
		table = new Table();
		
		// Datos Jugador
		table.setMainPlayer(new Player("mainPlayer", principalView.getPlayerCoins()));
		Card[] cards = new Card[2];
		cards[0] = principalView.getCard1();
		cards[1] = principalView.getCard2();
		Hand hand = new Hand(cards);
		table.getMainPlayer().setRankHand(hand.getHandRange());
		table.getMainPlayer().setBet(principalView.getPlayerBetCoins());
		
		// Datos Oponente
		table.setOpponentPlayer(new Player("opponentPlayer", principalView.getOpponentCoins()));
		//TODO falta en la interfaz un combobox con la ultima accion ejecutada por el oponente
		table.getOpponentPlayer().setDecision(new Decision(Action.CALL,0));
		table.getOpponentPlayer().setBet(principalView.getOpponentBetCoins());
		if (principalView.getOpponentStrategy().equals("Agresivo"))
			table.getOpponentPlayer().setStrategy("AGGRESIVE");
		else
			table.getOpponentPlayer().setStrategy("TIGHT");
		
		// Datos Mesa
		//TODO setear valor luz
		table.setBigBlind(20);
		if (principalView.isPlayerBigBlind()){
			table.getMainPlayer().setPosition("BIGBLIND");
			table.setPotSize(2*table.getBigBlind() + table.getOpponentPlayer().getBet());			
		}else{
			table.getMainPlayer().setPosition("SMALLBLIND");
			table.setPotSize(table.getBigBlind() + table.getBigBlind()/2);
		}
		decide(table);
		
	}
	
	private void decide(Table table){
		Decision decision = applyRules(table);
		String recomendation = null;
		if (decision != null){
			if (decision.getActionDesc() != null)
				recomendation = decision.getActionDesc();
			else
				recomendation = decision.getAction().getName();
			
		}
		if (recomendation == null)
			recomendation = "No se aplico ninguna regla";
        recomendationView = new Recomendacion(recomendation, principalView);
        recomendationView.setVisible(true);
        recomendationView.addRecomendationListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
            	getOtherDecision();
            }
        });
	}
	
	private void getOtherDecision(){
		aumentoView = new Aumento();
		aumentoView.setVisible(true);
		aumentoView.addContinueListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
            		table.getMainPlayer().setBet(aumentoView.getPlayerBet());
            		table.getOpponentPlayer().setBet(aumentoView.getOpponentBet());
            		table.setPotSize(table.getPotSize() + aumentoView.getPlayerBet() + aumentoView.getOpponentBet());
            		aumentoView.setVisible(false);
            		decide(table);
            }
        });
        recomendationView.setVisible(false);
	}
	
	public Decision applyRules(Table table){
		try {
			KnowledgeBase kbase = FactoryDRL.readKnowledgeBase("pokerRules.drl");
			StatefulKnowledgeSession ksession = kbase.newStatefulKnowledgeSession();
			ksession.insert(table);
			ksession.fireAllRules();
			return table.getMainPlayer().getDecision();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}
	
	
	public static void main(String args[]) {
        MainController controller = new MainController();
        controller.runApp();
    }
	
	
	

}
