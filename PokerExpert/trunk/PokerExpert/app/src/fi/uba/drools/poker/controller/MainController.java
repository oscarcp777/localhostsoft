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
import fi.uba.drools.poker.utils.Constants;
import fi.uba.drools.poker.view.Aumento;
import fi.uba.drools.poker.view.Principal;
import fi.uba.drools.poker.view.Recomendacion;

/**
 * Controlador principal de la aplicaci�n y punto de entrada de la misma
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
		principalView.addResetButtonListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
            	resetPrincipalView();
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
		table.getMainPlayer().setHand(hand);
		table.getMainPlayer().setDecision(new Decision(Action.CONTINUE,0));
		table.getMainPlayer().setBet(principalView.getPlayerBetCoins());
		
		// Datos Oponente
		table.setOpponentPlayer(new Player("opponentPlayer", principalView.getOpponentCoins()));
		//TODO falta en la interfaz un combobox con la ultima accion ejecutada por el oponente
		table.getOpponentPlayer().setDecision(new Decision(Action.CALL,0));
		table.getOpponentPlayer().setBet(principalView.getOpponentBetCoins());
		if (principalView.getOpponentStrategy().equals("Agresivo"))
			table.getOpponentPlayer().setStrategy(Constants.Strategy.AGGRESIVE);
		else
			table.getOpponentPlayer().setStrategy(Constants.Strategy.TIGHT);
		
		// Datos Mesa
		//TODO setear valor luz
		table.setBigBlind(principalView.getBigBlind());
		if (principalView.isPlayerBigBlind()){
			table.getMainPlayer().setPosition(Constants.Blind.BIG_BLIND);
			table.setPotSize(2*table.getBigBlind() + table.getOpponentPlayer().getBet());			
		}else{
			table.getMainPlayer().setPosition(Constants.Blind.SMALL_BLIND);
			table.setPotSize(table.getBigBlind() + table.getBigBlind()/2);
		}
		decide(table);
		
	}
	
	@SuppressWarnings("serial")
	private void decide(Table table){
		System.out.println("la mano es "+table.getMainPlayer().getHand()+" el rango de mano es: "+ table.getMainPlayer().getRankHand());
		System.out.println("la posicion es "+table.getMainPlayer().getPosition()+" la accion del rival es "+ table.getOpponentPlayer().getDecision().getAction());
		
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
        recomendationView = new Recomendacion(recomendation, principalView){

			@Override
			public void reset() {
				recomendationView.setVisible(false);
				resetPrincipalView();
			}
        	
        };
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
				
				if(table.getOpponentPlayer().getCash()==aumentoView.getOpponentBet()){
					table.getOpponentPlayer().setDecision(new Decision(Action.ALL_IN,0));
				}else{
					table.getOpponentPlayer().setDecision(new Decision(Action.RE_RAISE,0));
				}
				table.getOpponentPlayer().setBet(aumentoView.getOpponentBet());
				table.setPotSize(table.getPotSize() + aumentoView.getPlayerBet() + aumentoView.getOpponentBet());
				aumentoView.setVisible(false);
				decide(table);
			}
		});
		recomendationView.setVisible(false);
	}
	
	private void resetPrincipalView(){
		this.initialize();
		this.principalView.setVisible(true);
	}
	
	private Decision applyRules(Table table){
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
