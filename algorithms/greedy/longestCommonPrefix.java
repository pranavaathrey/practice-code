class lCP {
    public String longestCommonPrefix(String[] strs) {
        if(strs == null || strs.length == 0) return "";
        int index = 0, len = strs.length;
        boolean flag = true;

        int min = 201;
        for(int i = 0; i < len; i++) {
            min = Math.min(strs[i].length(), min);
        }        
        while(flag && index < min) {
            for(int i = 0; i < len && index < min; i++) {
                if(strs[i].charAt(index) != strs[0].charAt(index)){
                    flag = false;
                    break;
                } 
            }
            if(flag) index++;
        }
        return strs[0].substring(0, index);
    }
}