package fi.uba.drools.poker.models;

public class Table {
	
	private Player mainPlayer;
	private Player opponentPlayer;
	private Integer bigBlind;
	public Integer getBigBlind() {
		return bigBlind;
	}
	public void setBigBlind(Integer bigBlind) {
		this.bigBlind = bigBlind;
	}
	public Integer getSmallBlind() {
		return smallBlind;
	}
	public void setSmallBlind(Integer smallBlind) {
		this.smallBlind = smallBlind;
	}
	private Integer smallBlind;
	public Player getMainPlayer() {
		return mainPlayer;
	}
	public void setMainPlayer(Player mainPlayer) {
		this.mainPlayer = mainPlayer;
	}
	public Player getOpponentPlayer() {
		return opponentPlayer;
	}
	public void setOpponentPlayer(Player opponentPlayer) {
		this.opponentPlayer = opponentPlayer;
	}


}
