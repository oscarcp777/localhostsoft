package fi.uba.drools.poker.models;

/**
 * A Texas Hold'em poker action.
 * 
 * @author Oscar Stigter
 */
public enum Action {
    
    /** Posting the small blind. */
    SMALL_BLIND("Small Blind", "posts the small blind"),

    /** Posting the big blind. */
    BIG_BLIND("Big Blind", "posts the big blind"),
    
    /** Checking. */
    CHECK("Pasar", "checks"),
    
    /** Calling a bet. */
    CALL("Pagar", "calls"),
    
    /** Place an initial bet. */
    BET("Apostar", "bets"),
    
    /** Raising the current bet. */
    RAISE("Subir", "raises"),
    
    /** Re Raising the current bet. */
    RE_RAISE("Re Subir", "re raises"),
    
    /** Folding. */
    FOLD("Dejar la mano", "folds"),
    
    /** Continuing the game. */
    ALL_IN("apostar todo", "all in"),
    
    /** Continuing the game. */
    CONTINUE("Continue", "continues"),
    
    ;
    
    /** The name. */
    private final String name;
    
    /** The verb. */
    private final String verb;
    
    /**
     * Constructor.
     * 
     * @param name
     *            The name.
     */
    Action(String name, String verb) {
        this.name = name;
        this.verb = verb;
    }
    
    /**
     * Returns the name.
     * 
     * @return The name.
     */
    public String getName() {
        return name;
    }
    
    /**
     * Returns the verb form of this action.
     * 
     * @return The verb.
     */
    public String getVerb() {
        return verb;
    }
    
    /*
     * (non-Javadoc)
     * @see java.lang.Enum#toString()
     */
    @Override
    public String toString() {
        return name;
    }

}
