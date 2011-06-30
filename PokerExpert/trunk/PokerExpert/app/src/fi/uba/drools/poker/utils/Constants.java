package fi.uba.drools.poker.utils;

public interface Constants {
	public static final String COLOR_LETRAS="#000000";
	public static final String COLOR_LETRAS_COMPONENT="#000000";
	public static final String COLOR_COMPONENT="#ffffff";
	public static final String IMAGEN_FONDO="images/fondoPoker.jpg";
	public interface Atributos{
		public static final String POTSIZE="POTSIZE";
		public static final String MAIN_PLAYER_CASH="MAIN_PLAYER_CASH";
		public static final String POSITION_MAIN_PLAYER="POSITION_MAIN_PLAYER";
		public static final String OPPONENT_PLAYER_CASH="OPPONENT_PLAYER_CASH";
		public static final String DECISION_ACTION_OPPONENT="DECISION_ACTION_OPPONENT";
		public static final String BIG_BLIND="BIG_BLIND";
		public static final String STRATEGY_OPPONENT_PLAYER="STRATEGY_OPPONENT_PLAYER";
		public static final String HAND_MAIN_PLAYER = "HAND_MAIN_PLAYER";
		public static final String BET_MAIN_PLAYER = "BET_MAIN_PLAYER";
		public static final String BET_OPPONENT_PLAYER = "BET_OPPONENT_PLAYER";
	}
	public interface Blind{
		public static final String BIG_BLIND="BIG_BLIND";
		public static final String SMALL_BLIND="SMALL_BLIND";
	}
	public interface Strategy{
		public static final String AGGRESIVE="AGGRESIVE";
		public static final String TIGHT="TIGHT";
	}
	
}
