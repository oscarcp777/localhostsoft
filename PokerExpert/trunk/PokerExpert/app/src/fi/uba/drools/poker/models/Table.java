package fi.uba.drools.poker.models;

public class Table {
	
	public Player mainPlayer;
	public Player opponentPlayer;
	public Integer bigBlind;
	public Integer potSize;
	private Boolean firstBet;
    public Boolean getFirstBet() {
		return firstBet;
	}
	public void setFirstBet(Boolean firstBet) {
		this.firstBet = firstBet;
	}
	public Integer getPotSize() {
		return potSize;
	}
	public void setPotSize(Integer potSize) {
		this.potSize = potSize;
	}
	@Override
	public String toString() {
		StringBuilder builder = new StringBuilder();
		builder.append("Datos de la mesa:[ ");
		if (bigBlind != null) {
			builder.append("Luz Grande=");
			builder.append(bigBlind);
			builder.append(",");
		}
		if (potSize != null) {
			builder.append("Tamaño pozo=");
			builder.append(potSize);
			builder.append("] \n  ");
		}
		if (mainPlayer != null) {
			builder.append("Datos Jugador:");
			builder.append(mainPlayer);
			builder.append(" \n  ");
		}
		if (opponentPlayer != null) {
			builder.append("Datos Oponente=");
			builder.append(opponentPlayer);
		}
		
		return builder.toString();
	}
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
